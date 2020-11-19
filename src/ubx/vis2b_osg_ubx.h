/*
 * vis2b_osg_ubx microblx function block (autogenerated, don't edit)
 */

#include <ubx.h>

UBX_MODULE_LICENSE_SPDX(LGPL3)

/* includes types and type metadata */
#include <dyn2b/types/geometry.h>
#include "gc_pose.h.hexarr"

ubx_type_t types[] = {
	def_struct_type(struct gc_pose, &gc_pose_h),
};

/* block meta information */
char vis2b_osg_ubx_meta[] =
	" { doc='',"
	"   realtime=false,"
	"}";

/* declaration of block configuration */
ubx_proto_config_t vis2b_osg_ubx_config[] = {
	{ .name="nr_joints", .type_name = "int", .min=1, .max=1, .doc="Number of joints" },
	{ .name="mesh_base", .type_name = "char", .min=0, .max=0, .doc="Directory from which meshes should be loaded" },
	{ .name="mesh_names", .type_name = "char", .min=0, .max=0, .doc="Colon-separated list of mesh file names" },
	{ 0 },
};

/* declaration port block ports */
ubx_proto_port_t vis2b_osg_ubx_ports[] = {
	{ .name="poses", .in_type_name="struct gc_pose", .in_data_len=1, .doc="Array of poses for each link in the kinematic chain"  },
	{ 0 },
};

/* declare a struct port_cache */
struct vis2b_osg_ubx_port_cache {
	ubx_port_t* poses;
};

/* helper function to cache ports. call in init */
static void update_port_cache(ubx_block_t *b, struct vis2b_osg_ubx_port_cache *pc)
{
	pc->poses = ubx_port_get(b, "poses");
}

/* define safe accessors for the new types */
def_type_accessors(gc_pose, struct gc_pose);

/* block operation forward declarations */
int vis2b_osg_ubx_init(ubx_block_t *b);
int vis2b_osg_ubx_start(ubx_block_t *b);
void vis2b_osg_ubx_cleanup(ubx_block_t *b);
void vis2b_osg_ubx_step(ubx_block_t *b);

ubx_proto_block_t vis2b_osg_ubx_block = {
	.name = "vis2b/osg",
	.type = BLOCK_TYPE_COMPUTATION,
	.meta_data = vis2b_osg_ubx_meta,
	.configs = vis2b_osg_ubx_config,
	.ports = vis2b_osg_ubx_ports,

	/* ops */
	.init = vis2b_osg_ubx_init,
	.start = vis2b_osg_ubx_start,
	.cleanup = vis2b_osg_ubx_cleanup,
	.step = vis2b_osg_ubx_step,
};


/* vis2b_osg_ubx module init and cleanup functions */
int vis2b_osg_ubx_mod_init(ubx_node_t* nd)
{
	ubx_log(UBX_LOGLEVEL_DEBUG, nd, "vis2b/osg", __func__);

	for (unsigned int i=0; i<ARRAY_SIZE(types); i++) {
		if(ubx_type_register(nd, &types[i]) != 0)
			return -1;
	}

	if(ubx_block_register(nd, &vis2b_osg_ubx_block) != 0)
		return -1;

	return 0;
}

void vis2b_osg_ubx_mod_cleanup(ubx_node_t *nd)
{
	ubx_log(UBX_LOGLEVEL_DEBUG, nd, "vis2b/osg", __func__);

	for (unsigned int i=0; i<ARRAY_SIZE(types); i++)
		ubx_type_unregister(nd, types[i].name);

	ubx_block_unregister(nd, "vis2b/osg");
}

/* declare module init and cleanup functions, so that the ubx core can
 * find these when the module is loaded/unloaded */
UBX_MODULE_INIT(vis2b_osg_ubx_mod_init)
UBX_MODULE_CLEANUP(vis2b_osg_ubx_mod_cleanup)
