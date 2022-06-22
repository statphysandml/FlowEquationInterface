#include <flowequations/jacobian_equation.hpp>


namespace flowequations {
    devdat::DevDatC compute_jacobian_elements(const devdat::DevDatC &coordinates, JacobianEquationsWrapper * jacobian_equations)
    {
        const uint dim = coordinates.dim_size();
        auto number_of_coordinates = coordinates.n_elems();
        devdat::DevDatC jacobian_elements(pow(dim, 2), number_of_coordinates);
        // Evaluate jacobian for each element separately
        for(auto matrix_idx = 0; matrix_idx < pow(dim, 2); matrix_idx ++) {
            (*jacobian_equations)(jacobian_elements[matrix_idx], coordinates, matrix_idx);
        }
        return std::move(jacobian_elements);
    }


    void compute_jacobian_elements(const devdat::DevDatC &coordinates, devdat::DevDatC &jacobian_elements, JacobianEquationsWrapper * jacobian_equations)
    {
        // Evaluate jacobian for each element separately
        for(auto matrix_idx = 0; matrix_idx < pow(coordinates.dim_size(), 2); matrix_idx ++) {
            (*jacobian_equations)(jacobian_elements[matrix_idx], coordinates, matrix_idx);
        }
    }
}
