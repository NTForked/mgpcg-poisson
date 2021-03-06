//#####################################################################
// Copyright 2002-2006, Zhaosheng Bao, Robert Bridson, Ronald Fedkiw, Eran Guendelman, Geoffrey Irving, Sergey Koltakov, Frank Losasso, Andrew Selle, Tamar Shinar, Joseph Teran.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Class POLICY_UNIFORM 
//#####################################################################
#ifndef __POLICY_UNIFORM__
#define __POLICY_UNIFORM__

#include <Grids/GRID_POLICY.h>
#include <Advection_Equations/ADVECTION_FORWARD.h>
#include <Arrays/ARRAYS_FORWARD.h>
#include <Boundaries/BOUNDARY_FORWARD.h>
#include <Utilities/TYPE_UTILITIES.h>
namespace PhysBAM{

template<class T_GRID> class MPI_UNIFORM_GRID;
template<class T_GRID> class LAPLACE_UNIFORM;
template<class T_GRID> class PROJECTION_UNIFORM;
template<class T2,class T_GRID> class EXTRAPOLATION_UNIFORM;
template<class T_GRID> class FLUID_COLLISION_BODY_LIST_UNIFORM;
template<class T_GRID> class PARTICLE_LEVELSET_UNIFORM;
template<class T_GRID> class PARTICLE_LEVELSET_EVOLUTION_UNIFORM;
template<class T_GRID> class LEVELSET_MULTIPLE_UNIFORM;
template<class T_GRID> class FAST_LEVELSET;
template<class T_GRID> class BLOCK_UNIFORM;
template<class TV> class LEVELSET_IMPLICIT_OBJECT;

template<class TV> struct UNIFORM_TAG{};

template<class TV,class T_GRID=typename GRID_POLICY<TV>::UNIFORM_GRID> class POLICY_UNIFORM;

template<class T,int d,class T_GRID>
class POLICY_UNIFORM<VECTOR<T,d>,T_GRID>
{
    typedef VECTOR<T,d> TV;typedef VECTOR<int,d> TV_INT;
public:
    typedef UNIFORM_TAG<TV> GRID_TAG;

    typedef T SCALAR;
    typedef TV VECTOR_T;
    typedef TV_INT VECTOR_INT;
    typedef TV_INT INDEX;
    typedef VECTOR<T,d+2> VECTOR_T_EULER;

    typedef BLOCK_UNIFORM<T_GRID> BLOCK;
    typedef LAPLACE_UNIFORM<T_GRID> LAPLACE;
    typedef PROJECTION_UNIFORM<T_GRID> PROJECTION;
    typedef EXTRAPOLATION_UNIFORM<T_GRID,T> EXTRAPOLATION_SCALAR;
    typedef EXTRAPOLATION_UNIFORM<T_GRID,TV> EXTRAPOLATION_VECTOR;
    typedef FLUID_COLLISION_BODY_LIST_UNIFORM<T_GRID> FLUID_COLLISION_BODY_LIST;
    typedef PARTICLE_LEVELSET_UNIFORM<T_GRID> PARTICLE_LEVELSET;
    typedef PARTICLE_LEVELSET_EVOLUTION_UNIFORM<T_GRID> PARTICLE_LEVELSET_EVOLUTION;
    typedef PhysBAM::LEVELSET_IMPLICIT_OBJECT<TV> LEVELSET_IMPLICIT_OBJECT;
    typedef LEVELSET_MULTIPLE_UNIFORM<T_GRID> LEVELSET_MULTIPLE;
    typedef PhysBAM::FAST_LEVELSET<T_GRID> FAST_LEVELSET;
    typedef MPI_UNIFORM_GRID<T_GRID> MPI_GRID;
    typedef T_GRID PARALLEL_GRID;

    typedef typename IF<d==1,ARRAYS_1D<T>,typename IF<d==2,ARRAYS_2D<T>,ARRAYS_3D<T> >::TYPE>::TYPE ARRAYS_SCALAR;
    typedef typename IF<d==1,FACE_ARRAYS_1D<T>,typename IF<d==2,FACE_ARRAYS_2D<T>,FACE_ARRAYS_3D<T> >::TYPE>::TYPE FACE_ARRAYS;

    typedef BOUNDARY_UNIFORM<T_GRID,T> BOUNDARY_SCALAR;
    typedef PhysBAM::BOUNDARY_REFLECTION<T_GRID,T> BOUNDARY_REFLECTION;
    typedef PhysBAM::BOUNDARY_PHI_WATER<T_GRID> BOUNDARY_PHI_WATER; 
    typedef PhysBAM::BOUNDARY_MAC_GRID_SOLID_WALL_SLIP<T_GRID> BOUNDARY_MAC_GRID_SOLID_WALL_SLIP;

    // normal
    typedef FACE_LOOKUP_UNIFORM<T_GRID> FACE_LOOKUP;
    typedef AVERAGING_UNIFORM<T_GRID> AVERAGING;
    typedef INTERPOLATION_UNIFORM<T_GRID,T> INTERPOLATION_SCALAR;
    typedef LINEAR_INTERPOLATION_UNIFORM<T_GRID,T> LINEAR_INTERPOLATION_SCALAR;
    typedef LINEAR_INTERPOLATION_UNIFORM<T_GRID,TV> LINEAR_INTERPOLATION_VECTOR;
    typedef ADVECTION_SEMI_LAGRANGIAN_UNIFORM<T_GRID,T> ADVECTION_SEMI_LAGRANGIAN_SCALAR;
    typedef ADVECTION_HAMILTON_JACOBI_WENO<T_GRID,T> ADVECTION_HAMILTON_JACOBI_WENO_SCALAR;
    // collidable
    typedef FACE_LOOKUP_COLLIDABLE_UNIFORM<T_GRID> FACE_LOOKUP_COLLIDABLE;
    typedef LINEAR_INTERPOLATION_COLLIDABLE_CELL_UNIFORM<T_GRID,T> LINEAR_INTERPOLATION_COLLIDABLE_CELL_SCALAR;
    typedef LINEAR_INTERPOLATION_COLLIDABLE_FACE_UNIFORM<T_GRID,T> LINEAR_INTERPOLATION_COLLIDABLE_FACE_SCALAR;
    typedef ADVECTION_SEMI_LAGRANGIAN_COLLIDABLE_CELL_UNIFORM<T_GRID,T> ADVECTION_SEMI_LAGRANGIAN_COLLIDABLE_CELL;
    typedef ADVECTION_SEMI_LAGRANGIAN_COLLIDABLE_FACE_UNIFORM<T_GRID> ADVECTION_SEMI_LAGRANGIAN_COLLIDABLE_FACE;
    // multiphase fire
    typedef FACE_LOOKUP_FIRE_MULTIPHASE_UNIFORM<T_GRID> FACE_LOOKUP_FIRE_MULTIPHASE;
    typedef AVERAGING_UNIFORM<T_GRID,FACE_LOOKUP_FIRE_MULTIPHASE> AVERAGING_FIRE_MULTIPHASE;
    typedef LINEAR_INTERPOLATION_UNIFORM<T_GRID,T,FACE_LOOKUP_FIRE_MULTIPHASE> LINEAR_INTERPOLATION_FIRE_MULTIPHASE;
    typedef ADVECTION_SEMI_LAGRANGIAN_UNIFORM<T_GRID,T,AVERAGING_FIRE_MULTIPHASE,LINEAR_INTERPOLATION_FIRE_MULTIPHASE> ADVECTION_SEMI_LAGRANGIAN_FIRE_MULTIPHASE;
    typedef ADVECTION_WRAPPER_FIRE_MULTIPHASE_UNIFORM<T_GRID,T,ADVECTION_SEMI_LAGRANGIAN_FIRE_MULTIPHASE> ADVECTION_WRAPPER_SEMI_LAGRANGIAN_FIRE_MULTIPHASE;
    // multiphase fire collidable
    typedef FACE_LOOKUP_COLLIDABLE_UNIFORM<T_GRID,FACE_LOOKUP_FIRE_MULTIPHASE> FACE_LOOKUP_FIRE_MULTIPHASE_COLLIDABLE;
    typedef ADVECTION_SEMI_LAGRANGIAN_COLLIDABLE_FACE_UNIFORM<T_GRID,FACE_LOOKUP_FIRE_MULTIPHASE_COLLIDABLE> ADVECTION_SEMI_LAGRANGIAN_FIRE_MULTIPHASE_COLLIDABLE;
    typedef ADVECTION_WRAPPER_COLLIDABLE_FACE<T_GRID,T,FACE_LOOKUP_FIRE_MULTIPHASE,ADVECTION_SEMI_LAGRANGIAN_FIRE_MULTIPHASE_COLLIDABLE> NESTED_ADVECTION_WRAPPER_SEMI_LAGRANGIAN_FIRE_MULTIPHASE_COLLIDABLE;
    typedef ADVECTION_WRAPPER_FIRE_MULTIPHASE_UNIFORM<T_GRID,T,NESTED_ADVECTION_WRAPPER_SEMI_LAGRANGIAN_FIRE_MULTIPHASE_COLLIDABLE> ADVECTION_WRAPPER_SEMI_LAGRANGIAN_FIRE_MULTIPHASE_COLLIDABLE;
//#####################################################################
};
}
#endif
