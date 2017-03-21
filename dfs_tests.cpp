#include "dfs.h"

#include <boost/test/included/unit_test.hpp>
using namespace boost::unit_test;


void empty_graph()
{
	BOOST_TEST(DetectCycleMatrix({}) == false);
}

void broken_graph()
{
	BOOST_CHECK_THROW(DetectCycleMatrix({ { 0, 1 } }), std::invalid_argument);
	BOOST_CHECK_THROW(DetectCycleMatrix({ { 0, 1, 0, 1, 0 },{ 0, 0, 0, 1, 0 } }), std::invalid_argument);
}

void trivial_graph()
{
	BOOST_TEST(DetectCycleMatrix({ {0} }) == false);
	BOOST_TEST(DetectCycleMatrix({ {1} }) == true);
	
	BOOST_TEST(DetectCycleMatrix({ { 0, 0 },{ 0, 0 } }) == false);
	BOOST_TEST(DetectCycleMatrix({ { 1, 0 },{ 0, 1 } }) == true);
	BOOST_TEST(DetectCycleMatrix({ { 0, 1 },{ 1, 0 } }) == true);
	BOOST_TEST(DetectCycleMatrix({ { 1, 1 },{ 1, 1 } }) == true);
	
	BOOST_TEST(DetectCycleMatrix({ { 0, 1, 1 },{ 0, 0, 1 },{ 0, 0, 0 } }) == false);
	BOOST_TEST(DetectCycleMatrix({ { 0, 1, 0 },{ 0, 0, 1 },{ 1, 0, 0 } }) == true);
	BOOST_TEST(DetectCycleMatrix({ { 0, 0, 1 },{ 1, 0, 0 },{ 0, 1, 0 } }) == true);
	BOOST_TEST(DetectCycleMatrix({ { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } }) == false);

	BOOST_TEST(DetectCycleMatrix({ { 0, 0, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 1, 0 },{ 0, 1, 0, 0 } }) == true);
}

void complicated_graph()
{
	enum { A = 0, B, C, D, E, F, G };
	std::vector< std::vector<bool> > g(7, std::vector<bool>(7));
	//A->B,F
	g[A][B] = g[A][F] = 1;
	//B->C,D
	g[B][C] = g[B][D] = 1;
	//D->E
	g[D][E] = 1;
	//F->G
	g[F][G] = 1;
	BOOST_TEST(DetectCycleMatrix(g) == false);

	//add 2 cross edges
	g[E][C] = g[G][E] = 1;
	BOOST_TEST(DetectCycleMatrix(g) == false);

	//add 1 fwd edge
	g[B][E] = 1;
	BOOST_TEST(DetectCycleMatrix(g) == false);

	//add backward edge
	auto g2 = g;
	g2[C][A] = 1;
	BOOST_TEST(DetectCycleMatrix(g2) == true);
	auto g3 = g;
	g3[G][A] = 1;
	BOOST_TEST(DetectCycleMatrix(g2) == true);
	auto g4 = g;
	g4[E][B] = 1;
	BOOST_TEST(DetectCycleMatrix(g4) == true);
}

void complicated_graph2()
{
	enum { A = 0, B, C, D, E, F };
	std::vector< std::vector<bool> > g(6, std::vector<bool>(6));
	//A->B,D
	g[A][B] = g[A][D] = 1;
	//B->E
	g[B][E] = 1;
	//C->E->F
	g[C][E] = g[C][F] = 1;
	//E->D
	g[E][D] = 1;
	BOOST_TEST(DetectCycleMatrix(g) == false);

	//add
	//F->F
	auto g2 = g;
	g2[F][F] = 1;
	BOOST_TEST(DetectCycleMatrix(g2) == true);
	//B->D
	auto g3 = g;
	g3[B][D] = 1;
	BOOST_TEST(DetectCycleMatrix(g3) == false);
};


test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	auto& master = framework::master_test_suite();
	master.add(BOOST_TEST_CASE(&empty_graph));
	master.add(BOOST_TEST_CASE(&broken_graph));
	master.add(BOOST_TEST_CASE(&trivial_graph));
	master.add(BOOST_TEST_CASE(&complicated_graph));
	master.add(BOOST_TEST_CASE(&complicated_graph2));
	return 0;
}
