#include "gtest/gtest.h"
#include "alps/gf/mesh.hpp"
#include "gf_test.hpp"

TEST(Mesh,CompareMatsubara) {
  alps::gf::matsubara_mesh<alps::gf::mesh::POSITIVE_NEGATIVE> mesh1(5.0, 20);
  alps::gf::matsubara_mesh<alps::gf::mesh::POSITIVE_NEGATIVE> mesh2(5.0, 20);
  alps::gf::matsubara_mesh<alps::gf::mesh::POSITIVE_NEGATIVE> mesh3(4.0, 20);

  EXPECT_TRUE(mesh1==mesh2);
  EXPECT_TRUE(mesh1!=mesh3);

  EXPECT_FALSE(mesh1==mesh3);
  EXPECT_FALSE(mesh1!=mesh2);

}

TEST(Mesh,CompareITime) {
  alps::gf::itime_mesh mesh1(5.0, 20);
  alps::gf::itime_mesh mesh2(5.0, 20);
  alps::gf::itime_mesh mesh3(4.0, 20);

  EXPECT_TRUE(mesh1==mesh2);
  EXPECT_TRUE(mesh1!=mesh3);

  EXPECT_FALSE(mesh1==mesh3);
  EXPECT_FALSE(mesh1!=mesh2);
}

TEST(Mesh,CompareMomentum) {
  alps::gf::momentum_index_mesh::container_type points1(boost::extents[20][3]);
  alps::gf::momentum_index_mesh::container_type points2(boost::extents[20][3]);
  alps::gf::momentum_index_mesh::container_type points3(boost::extents[20][3]);
  alps::gf::momentum_index_mesh::container_type points4(boost::extents[3][20]);
  for (int i=0; i<points1.num_elements(); ++i) {
    *(points1.origin()+i)=i;
    *(points2.origin()+i)=i;
    *(points3.origin()+i)=i+1;
    *(points4.origin()+i)=i;
  }

  alps::gf::momentum_index_mesh mesh1(points1);
  alps::gf::momentum_index_mesh mesh2(points2);
  alps::gf::momentum_index_mesh mesh3(points3);
  alps::gf::momentum_index_mesh mesh4(points4);

  EXPECT_TRUE(mesh1==mesh2);
  EXPECT_TRUE(mesh1!=mesh3);
  EXPECT_TRUE(mesh1!=mesh4);

  EXPECT_FALSE(mesh1==mesh3);
  EXPECT_FALSE(mesh1!=mesh2);
  EXPECT_FALSE(mesh1==mesh4);
}


TEST(Mesh,CompareRealSpace) {
  alps::gf::real_space_index_mesh::container_type points1(boost::extents[20][3]);
  alps::gf::real_space_index_mesh::container_type points2(boost::extents[20][3]);
  alps::gf::real_space_index_mesh::container_type points3(boost::extents[20][3]);
  alps::gf::real_space_index_mesh::container_type points4(boost::extents[3][20]);
  for (int i=0; i<points1.num_elements(); ++i) {
    *(points1.origin()+i)=i;
    *(points2.origin()+i)=i;
    *(points3.origin()+i)=i+1;
    *(points4.origin()+i)=i;
  }

  alps::gf::real_space_index_mesh mesh1(points1);
  alps::gf::real_space_index_mesh mesh2(points2);
  alps::gf::real_space_index_mesh mesh3(points3);
  alps::gf::real_space_index_mesh mesh4(points4);

  EXPECT_TRUE(mesh1==mesh2);
  EXPECT_TRUE(mesh1!=mesh3);
  EXPECT_TRUE(mesh1!=mesh4);

  EXPECT_FALSE(mesh1==mesh3);
  EXPECT_FALSE(mesh1!=mesh2);
  EXPECT_FALSE(mesh1==mesh4);
}

TEST(Mesh,CompareIndex) {
  alps::gf::index_mesh mesh1(20);
  alps::gf::index_mesh mesh2(20);
  alps::gf::index_mesh mesh3(19);

  EXPECT_TRUE(mesh1==mesh2);
  EXPECT_TRUE(mesh1!=mesh3);

  EXPECT_FALSE(mesh1==mesh3);
  EXPECT_FALSE(mesh1!=mesh2);
}

TEST(Mesh,PrintMatsubaraMeshHeader) {
  double beta=5.;
  int n=20;
  {
    std::stringstream header_line;
    header_line << "# MATSUBARA mesh: N: "<<n<<" beta: "<<beta<<" statistics: "<<"FERMIONIC"<<" POSITIVE_ONLY"<<std::endl;
    alps::gf::matsubara_mesh<alps::gf::mesh::POSITIVE_ONLY> mesh1(beta, n);
    std::stringstream header_line_from_mesh;
    header_line_from_mesh << mesh1;
    EXPECT_EQ(header_line.str(), header_line_from_mesh.str());
  }
  {
    std::stringstream header_line;
    header_line << "# MATSUBARA mesh: N: "<<n<<" beta: "<<beta<<" statistics: "<<"FERMIONIC"<<" POSITIVE_NEGATIVE"<<std::endl;
    alps::gf::matsubara_mesh<alps::gf::mesh::POSITIVE_NEGATIVE> mesh1(beta, n);
    std::stringstream header_line_from_mesh;
    header_line_from_mesh << mesh1;
    EXPECT_EQ(header_line.str(), header_line_from_mesh.str());
  }

}

TEST(Mesh,PrintImagTimeMeshHeader) {
  double beta=5.;
  int ntau=200;
  std::stringstream header_line;
  header_line << "# IMAGINARY_TIME mesh: N: "<<ntau<<" beta: "<<beta<<" statistics: "<<"FERMIONIC"<<std::endl;
  alps::gf::itime_mesh mesh1(beta, ntau);
  std::stringstream header_line_from_mesh;
  header_line_from_mesh << mesh1;
  EXPECT_EQ(header_line.str(), header_line_from_mesh.str());
}
TEST(Mesh,PrintMomentumMeshHeader) {
  alps::gf::momentum_index_mesh::container_type data=get_data_for_momentum_mesh();
  std::stringstream header_line;
  header_line << "# MOMENTUM_INDEX mesh: N: "<<data.shape()[0]<<" dimension: "<<data.shape()[1]<<" points: ";
  for(int i=0;i<data.shape()[0];++i){
    header_line<<"(";
    for(int d=0;d<data.shape()[1]-1;++d){ header_line<<data[i][d]<<","; } header_line<<data[i][data.shape()[1]-1]<<") ";
  }
  header_line<<std::endl;
  alps::gf::momentum_index_mesh mesh1(data);
  std::stringstream header_line_from_mesh;
  header_line_from_mesh << mesh1;
  EXPECT_EQ(header_line.str(), header_line_from_mesh.str());
}
TEST(Mesh,PrintRealSpaceMeshHeader) {
  alps::gf::real_space_index_mesh::container_type data=get_data_for_real_space_mesh();
  std::stringstream header_line;
  header_line << "# REAL_SPACE_INDEX mesh: N: "<<data.shape()[0]<<" dimension: "<<data.shape()[1]<<" points: ";
  for(int i=0;i<data.shape()[0];++i){
    header_line<<"(";
    for(int d=0;d<data.shape()[1]-1;++d){ header_line<<data[i][d]<<","; } header_line<<data[i][data.shape()[1]-1]<<") ";
  }
  header_line<<std::endl;
  alps::gf::real_space_index_mesh mesh1(data);
  std::stringstream header_line_from_mesh;
  header_line_from_mesh << mesh1;
  EXPECT_EQ(header_line.str(), header_line_from_mesh.str());
}
TEST(Mesh,PrintIndexMeshHeader) {
  int n=2;
  std::stringstream header_line;
  header_line << "# INDEX mesh: N: "<<n<<std::endl;
  alps::gf::index_mesh mesh1(2);
  std::stringstream header_line_from_mesh;
  header_line_from_mesh << mesh1;
  EXPECT_EQ(header_line.str(), header_line_from_mesh.str());
}
