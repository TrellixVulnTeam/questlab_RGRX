/*
***************************************
*   Asylum3D @ 2014-12-23
***************************************
*/

#include "../../asylum.hpp"

/* Asylum Namespace */
namespace asy {

/******************************/
/* Wavefront Material (Fixed) */
/******************************/
class crh3d9_mtl_wf_fixed : public material_i
{
private:
    leng_t          m_anow;
    sWAVEFRONT      m_objs;
    crh3d9_mesh_wf* m_mesh;
    crh3d9_attr_wf* m_attr;

public:
    /* ================================================================================== */
    crh3d9_mtl_wf_fixed (const sWAVEFRONT* objs, crh3d9_mesh_wf* mesh, crh3d9_attr_wf* attr)
    {
        m_anow = 0;
        m_mesh = mesh;
        m_attr = attr;
        mem_cpy(&m_objs, objs, sizeof(sWAVEFRONT));
    }

    /* ========================= */
    virtual ~crh3d9_mtl_wf_fixed ()
    {
        wfront_obj_free(&m_objs);
        for (leng_t idx = 0; idx < m_objs.n_g; idx++)
            m_mesh[idx].free();
        mem_free(m_mesh);
        mem_free(m_attr);
    }

public:
    /* ========================== */
    virtual void commit (bool trans)
    {
        leng_t  aidx;

        for (leng_t idx = 0; idx < m_objs.n_g; idx++) {
            aidx = m_objs.p_g[idx].attr;
            if (aidx == 0)
                return;
            if (trans == m_attr[aidx - 1].trans()) {
                if (m_anow != aidx) {
                    m_anow = aidx;
                    m_attr[aidx - 1].apply_ff();
                }
                m_mesh[idx].apply_ss();
            }
        }
    }
};

}   /* namespace */

/* ========================================================================================= */
CR_API material_i* create_crh3d9_mtl_wf_fixed (const ansi_t* obj, bool_t swap_yz, bool_t neg_z,
                            const ansi_t* mtl, const asy::map_acs<asy::crh3d9_texr>* texpool,
                                                const asy::crh3d9_main* main)
{
    sWAVEFRONT              objs;
    asy::material_i*        mtrl;
    asy::crh3d9_mesh_wf*    mesh;
    asy::crh3d9_attr_wf*    attr;

    if (!wfront_obj_load(&objs, obj, swap_yz, neg_z))
        return (NULL);
    if (!wfront_mtl_load(&objs, mtl))
        goto _failure1;
    mesh = mem_talloc(objs.n_g, asy::crh3d9_mesh_wf);
    if (mesh == NULL)
        goto _failure1;
    for (leng_t idx = 0; idx < objs.n_g; idx++) {
        if (!mesh[idx].init2_ss(main, &objs, idx)) {
            for (leng_t ii = 0; ii < idx; ii++)
                mesh[ii].free();
            mem_free(mesh);
            goto _failure1;
        }
    }
    attr = mem_talloc(objs.n_m, asy::crh3d9_attr_wf);
    if (attr == NULL)
        goto _failure2;
    for (leng_t idx = 0; idx < objs.n_m; idx++) {
        if (!attr[idx].init(main, &objs.p_m[idx], texpool))
            goto _failure3;
    }
    mtrl = new asy::crh3d9_mtl_wf_fixed (&objs, mesh, attr);
    if (mtrl == NULL)
        goto _failure3;
    return ((material_i*)mtrl);

_failure3:
    mem_free(attr);
_failure2:
    for (leng_t idx = 0; idx < objs.n_g; idx++) {
        mesh[idx].free();
    mem_free(mesh);
_failure1:
    wfront_obj_free(&objs);
    return (NULL);
}
