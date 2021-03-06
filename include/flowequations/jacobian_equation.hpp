#ifndef FLOWEQUATIONS_JACOBIAN_EQUATION_HPP
#define FLOWEQUATIONS_JACOBIAN_EQUATION_HPP

#include <vector>
#include <string>
#include <memory>

#include <nlohmann/json.hpp>

#include <nlohmann/json.hpp>

#include <devdat/header.hpp>
#include <devdat/devdat.hpp>

using json = nlohmann::json;


namespace flowequations {
    class JacobianEquationsWrapper : public std::enable_shared_from_this<JacobianEquationsWrapper>
    {
    public:
        virtual void operator() (devdat::DimensionIteratorC &derivatives, const devdat::DevDatC &variables, const int row_idx, const int col_idx) = 0;
        
        virtual void operator() (devdat::DimensionIteratorC &derivatives, const devdat::DevDatC &variables, const int matrix_idx) = 0;
        
        virtual size_t get_dim() = 0;
        
        virtual json get_json() const {
            return {};
        }

        static std::string name()
        {
            return "jacobian_equation";
        }
    };

    struct JacobianEquation
    {
        virtual void operator() (devdat::DimensionIteratorC &derivatives, const devdat::DevDatC &variables) = 0;
    };

    template<typename JacobianEquations, typename... Args>
    std::shared_ptr<JacobianEquationsWrapper> generate_jacobian_equations(Args... args)
    {
        return std::make_shared<JacobianEquations>(args...);
    }

    devdat::DevDatC compute_jacobian_elements(const devdat::DevDatC &coordinates, JacobianEquationsWrapper * jacobian_equations);

    void compute_jacobian_elements(const devdat::DevDatC &coordinates, devdat::DevDatC &jacobian_elements, JacobianEquationsWrapper * jacobian_equations);
}

#endif //FLOWEQUATIONS_JACOBIAN_EQUATION_HPP
