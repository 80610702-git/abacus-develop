#ifndef ABFS_H
#define ABFS_H

#include "src_global/vector3.h"
#include "src_global/matrix.h"
#include "src_lcao/exx_abfs.h"

#include <set>
#include <vector>
#include <map>
#include <memory>

class Abfs
{
public:
	
	template<typename T> class Vector3_Order;

	// Cs[iat1][iat2][box2]
	// Cws[it1,it1,0][it2,R]
	// Vws[it1,0][it2,R]
	static map<size_t,map<size_t,map<Vector3_Order<int>,shared_ptr<matrix>>>> cal_Cs(
		const set<size_t> &atom_centres,
		const Exx_Abfs::Matrix_Orbs11 &m_abfs_abfs,
		const Exx_Abfs::Matrix_Orbs21 &m_abfslcaos_lcaos,
		const Element_Basis_Index::IndexLNM &index_abfs,
		const Element_Basis_Index::IndexLNM &index_lcaos,
		const double threshold,
		map<size_t,map<size_t,map<Vector3_Order<double>,weak_ptr<matrix>>>> &Cws,
		map<size_t,map<size_t,map<Vector3_Order<double>,weak_ptr<matrix>>>> &Vws );

	// Vs[iat1][iat2][box2]
	// Vws[it1,0][it2,R]
	static map<size_t,map<size_t,map<Vector3_Order<int>,shared_ptr<matrix>>>> cal_Vs(
		const vector<pair<size_t,size_t>> &atom_pairs,
		const vector<Vector3_Order<int>> &Coulomb_potential_boxes,
		const Exx_Abfs::Matrix_Orbs11 &m_abfs_abfs,
		const Element_Basis_Index::IndexLNM &index_abfs,
		const double rmesh_times,
		const double threshold,
		map<size_t,map<size_t,map<Vector3_Order<double>,weak_ptr<matrix>>>> &Vws );	
		
	// use matrixes ms to get period mps
	static map<Abfs::Vector3_Order<int>,shared_ptr<matrix>> 
		cal_mps(
			const Abfs::Vector3_Order<int> &Born_von_Karman_period,
			const map<Vector3_Order<int>,shared_ptr<matrix>> &ms );
	// mps[iat1][iat2][box2]
	static map<size_t,map<size_t,map<Abfs::Vector3_Order<int>,shared_ptr<matrix>>>> 
		cal_mps(
			const Abfs::Vector3_Order<int> &Born_von_Karman_period,
			const map<size_t,map<size_t,map<Vector3_Order<int>,shared_ptr<matrix>>>> &ms );

	// C[it1,it1,0][it2,R]
	static shared_ptr<matrix> DPcal_C( 
		const size_t &it1, 
		const size_t &it2, 
		const Vector3_Order<double> &R, 												// unit: ucell.lat0
		const Exx_Abfs::Matrix_Orbs11 &m_abfs_abfs,
		const Exx_Abfs::Matrix_Orbs21 &m_abfslcaos_lcaos,
		const Element_Basis_Index::IndexLNM &index_abfs,
		const Element_Basis_Index::IndexLNM &index_lcaos,
		const double threshold,
		const bool writable,
		map<size_t,map<size_t,map<Vector3_Order<double>,weak_ptr<matrix>>>> &Cws,
		map<size_t,map<size_t,map<Vector3_Order<double>,weak_ptr<matrix>>>> &Vws );

	// V[it1,0][it2,R]
	static shared_ptr<matrix> DPcal_V( 
		const size_t &it1, 
		const size_t &it2, 
		const Vector3_Order<double> &R, 												// unit: ucell.lat0
		const Exx_Abfs::Matrix_Orbs11 &m_abfs_abfs,
		const Element_Basis_Index::IndexLNM &index_abfs,
		const double threshold,
		const bool writable,
		map<size_t,map<size_t,map<Vector3_Order<double>,weak_ptr<matrix>>>> &Vws );		
		
//	static map<size_t,vector<Abfs::Vector3_Order<int>>> get_adjs( const size_t &T, const Vector3<double> &tau_cartesian );
	static map<size_t,vector<Abfs::Vector3_Order<int>>> get_adjs( const size_t &iat );
	static vector<map<size_t,vector<Abfs::Vector3_Order<int>>>> get_adjs();
	static set<pair<size_t,size_t>> get_H_pairs_core( const vector<pair<size_t,size_t>> &atom_pairs );

	static shared_ptr<matrix> cal_I( const shared_ptr<matrix> &m );
	static vector<vector<shared_ptr<matrix>>> cal_I( const vector<vector<shared_ptr<matrix>>> &ms );
	
	template<typename T1,typename T2,typename T3,typename T4>
	static void delete_empty_ptrs( map<T1,map<T2,map<T3,weak_ptr<T4>>>> &ptrs );
	template<typename T1,typename T2,typename T3,typename T4>
	static void delete_threshold_ptrs( map<T1,map<T2,map<T3,shared_ptr<T4>>>> &ptrs, const double threshold);

	template<typename T1, typename T2, typename Tother>
	static vector<pair<T1,T2>> get_atom_pair(const map<T1,map<T2,Tother>> &m);
};

#endif	// ABFS_H