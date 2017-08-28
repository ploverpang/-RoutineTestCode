#include <iostream>
#include <eigen3/Eigen/Eigen>
#include <ctime>

using namespace Eigen;

#define MATRIX_SIZE (50)

int main()
{
    MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(0,0)-m(1,0);

    Matrix<float, 3, 3> matrix3_3= Matrix3f::Random(3,3);
    Matrix<float, Eigen::Dynamic, Eigen::Dynamic> m_d;
    Vector3d v_3d;

    v_3d << 1,2,3;

    Eigen::Matrix<double, 3, 1> result_m = matrix3_3.cast<double>() * v_3d;

    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> m_nn = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1>  m_n1 = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock();
    Eigen::Matrix<double, MATRIX_SIZE, 1> r_inv = m_nn.inverse()*m_n1;
    std::cout << "time inverse is " << 1000*(clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms" <<  std::endl;
    std::cout << "r_inv is " << r_inv << std::endl;

    time_stt = clock();
    Eigen::Matrix<double, MATRIX_SIZE, 1> r_qr;
    r_qr = m_nn.colPivHouseholderQr().solve(m_n1);
    std::cout << "time qr is " << 1000*(clock() - time_stt)/(double)CLOCKS_PER_SEC << "ms" <<  std::endl;
    std::cout << "r_qr is " << r_qr << std::endl;

    //std::cout << "matrix3_3 "<< matrix3_3 << std::endl;
    //std::cout << "result_m" << result_m << std::endl;

    return 0;
}
