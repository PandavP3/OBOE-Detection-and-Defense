#include "gcc-plugin.h"
#include "plugin-version.h"
#include "tree.h"
#include "tree-pass.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "context.h"
#include "function.h"
#include "diagnostic.h"

int plugin_is_GPL_compatible;

static unsigned int oboe_analyzer_exec(void) {
    basic_block bb;
    FOR_ALL_BB_FN(bb, cfun) {
        gimple_stmt_iterator gsi;
        for (gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi)) {
            gimple *stmt = gsi_stmt(gsi);

            // Very basic check: detect assignments like arr[i] = ...;
            if (is_gimple_assign(stmt)) {
                tree lhs = gimple_assign_lhs(stmt);

                if (TREE_CODE(lhs) == ARRAY_REF) {
                    location_t loc = gimple_location(stmt);
                    warning_at(loc, 0, "(Plugin) Potential off-by-one index access");
                }
            }
        }
    }

    return 0;
}

namespace {
        const pass_data oboe_pass_data = {
         GIMPLE_PASS,         // type
         "oboe_plugin",       // name
         OPTGROUP_NONE,       // optinfo_flags
         TV_NONE,             // tv_id
         PROP_gimple_any,     // properties_required
         0                    // properties_provided
};


    struct oboe_pass : gimple_opt_pass {
        oboe_pass(gcc::context *ctx)
            : gimple_opt_pass(oboe_pass_data, ctx) {}

        unsigned int execute(function *) override {
            return oboe_analyzer_exec();
        }
    };
}

int plugin_init(struct plugin_name_args *plugin_info,
                struct plugin_gcc_version *version) {

    if (!plugin_default_version_check(version, &gcc_version)) {
        error("GCC plugin version mismatch");
        return 1;
    }

    printf("[Plugin] Initializing OBOE plugin...\n");

    struct register_pass_info pass_info;
    pass_info.pass = new oboe_pass(g);
    pass_info.reference_pass_name = "cfg";
    pass_info.ref_pass_instance_number = 1;
    pass_info.pos_op = PASS_POS_INSERT_AFTER;

    register_callback(plugin_info->base_name, PLUGIN_PASS_MANAGER_SETUP, nullptr, &pass_info);

    return 0;
}

