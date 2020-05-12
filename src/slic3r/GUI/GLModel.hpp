#ifndef slic3r_GLModel_hpp_
#define slic3r_GLModel_hpp_

#include "libslic3r/Point.hpp"
#include "libslic3r/BoundingBox.hpp"
#include <vector>

namespace Slic3r {

class TriangleMesh;

namespace GUI {

    struct GLModelInitializationData
    {
        std::vector<Vec3f> positions;
        std::vector<Vec3f> normals;
        std::vector<Vec3i> triangles;
    };

    class GL_Model
    {
        unsigned int m_vbo_id{ 0 };
        unsigned int m_ibo_id{ 0 };
        size_t m_indices_count{ 0 };

        BoundingBoxf3 m_bounding_box;

    public:
        virtual ~GL_Model() { reset(); }

        void init_from(const GLModelInitializationData& data);
        void init_from(const TriangleMesh& mesh);
        void reset();
        void render() const;

        const BoundingBoxf3& get_bounding_box() const { return m_bounding_box; }

    private:
        void send_to_gpu(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    };


    // create an arrow with cylindrical stem and conical tip, with the given dimensions and resolution
    // the origin of the arrow is in the center of the stem cap
    // the arrow has its axis of symmetry along the Z axis and is pointing upward
    GLModelInitializationData stilized_arrow(int resolution, float tip_radius, float tip_height,
        float stem_radius, float stem_height);

} // namespace GUI
} // namespace Slic3r

#endif // slic3r_GLModel_hpp_

