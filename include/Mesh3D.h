/*******************************************************************************
Copyright (c) 2015, Jonathan Hiller
To cite academic use of Voxelyze: Jonathan Hiller and Hod Lipson "Dynamic Simulation of Soft Multimaterial 3D-Printed Objects" Soft Robotics. March 2014, 1(1): 88-101.
Available at http://online.liebertpub.com/doi/pdfplus/10.1089/soro.2013.0010

This file is part of Voxelyze.
Voxelyze is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
Voxelyze is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
See <http://www.opensource.org/licenses/lgpl-3.0.html> for license details.
*******************************************************************************/

#ifndef MESH3D_H
#define MESH3D_H


//
//#include <vector>
//#include "../voxelyze/include/Vec3D.h"
//#include "XML_Rip.h"
//
////#include "VX_Object.h"
//
//#ifdef USE_OPEN_GL
//#include "GL_Utils.h" //really just need the CColor container from here
//#else
////basic RGB color container
//struct CColor { //copied from GL_Utils.h
//	CColor(){r=-1; g=-1; b=-1;a=-1;};
//	CColor (const CColor& C) {r = C.r; g = C.g; b = C.b; a = C.a;};
//	CColor(vfloat rIn, vfloat gIn, vfloat bIn, vfloat aIn=1.0){r=rIn; g=gIn; b=bIn; a=aIn;};
//	vfloat r, g, b, a;
//	bool isValid(void){if(r>=0.0 && r <=1.0 && g>=0.0 && g <=1.0 && b>=0.0 && b <=1.0 && a>=0.0 && a <=1.0) return true; else return false;};
//
//};
//#endif
//
////structure to hold each vertex
//struct CVertex {
//	CVertex() {n = Vec3D<>(0,0,0); v = Vec3D<>(0,0,0); VColor = CColor(1,1,1,1); DrawOffset = Vec3D<>(0,0,0);}
//	CVertex(const Vec3D<>& av) {n =  Vec3D<>(0,0,0); v = av; VColor = CColor(1,1,1,1); DrawOffset = Vec3D<>(0,0,0);}
//	CVertex(const Vec3D<>& an, const Vec3D<>& av) {n = an; v = av; VColor = CColor(1,1,1,1); DrawOffset = Vec3D<>(0,0,0);}
//	CVertex(const Vec3D<>& av, const CColor& ac) {n = Vec3D<>(0,0,0); v = av; VColor = ac; DrawOffset = Vec3D<>(0,0,0);}
//	inline CVertex& operator=(const CVertex& V) {n=V.n; v=V.v; VColor = V.VColor; DrawOffset = V.DrawOffset; return *this;}; //overload equals
//	CVertex(const CVertex& V) {*this = V;} // DrawAxis = V.DrawAxis; DrawAngle = V.DrawAngle;}
//	Vec3D<> OffPos(void) {return v+DrawOffset;} //return the deformed position to draw this one...
//
//	void WriteXML(CXML_Rip* pXML);
//	bool ReadXML(CXML_Rip* pXML);
//
//	Vec3D<> n; //normal
//	Vec3D<> v; //Vertex location
//	CColor VColor;
//	Vec3D<> DrawOffset; //apply offset to each point
//};
//
////structure to hold each facet
//struct CFacet {
//	CFacet() {n=Vec3D<>(0,0,0); FColor = CColor(1,1,1,1); vi[0] = 0; vi[1] = 0; vi[2] = 1; Name = -1;}
//	CFacet(const int& av1, const int& av2, const int& av3) { n = Vec3D<>(0,0,0); vi[0] = av1; vi[1] = av2; vi[2] = av3; FColor = CColor(1,1,1,1); Name = -1;}
//	CFacet(const Vec3D<>& an, const int& av1, const int& av2, const int& av3) { n = an; vi[0] = av1; vi[1] = av2; vi[2] = av3; FColor = CColor(1,1,1,1); Name = -1;}
//	CFacet(const Vec3D<>& an, const int& av1, const int& av2, const int& av3, const int& NIn) { n = an; vi[0] = av1; vi[1] = av2; vi[2] = av3; FColor = CColor(1,1,1,1); Name = NIn;}
//	CFacet(const Vec3D<>& an, const int& av1, const int& av2, const int& av3, const CColor& ac) { n = an; vi[0] = av1; vi[1] = av2; vi[2] = av3; FColor = ac; Name = -1;}
//	inline CFacet& operator=(const CFacet& p) { vi[0]=p.vi[0]; vi[1]=p.vi[1]; vi[2]=p.vi[2]; n=p.n; FColor = p.FColor; Name = p.Name; return *this;}; //overload equals
//	CFacet(const CFacet& p) {*this = p;}
//
//	Vec3D<> n; //normal
//	CColor FColor;
//	int vi[3]; //vertex indices
//	int Name; //my name (for GL picking)
//};
//
//struct CLine {
//	CLine() {}
//	CLine(const int& av1, const int& av2) {vi[0] = av1; vi[1] = av2;}
//	inline CLine& operator=(const CLine& l) { vi[0]=l.vi[0]; vi[1]=l.vi[1]; return *this;}; //overload equals
//	CLine(const CLine& l) {*this = l;}
//	friend bool operator<(const CLine& L1, const CLine& L2) { if (L1.vi[0] == L2.vi[0]) return L1.vi[1] < L2.vi[1]; else return L1.vi[0] < L2.vi[0];} //for sorting
//	friend bool operator==(const CLine& L1, const CLine& L2) {return ((L1.vi[0]==L2.vi[0] && L1.vi[1]==L2.vi[1]));} // || (vi[0]==O.vi[1] && vi[1]==O.vi[0]));} //Is equal
//
//	int vi[2];
//};

#include "Array3D.h"
#include "Vec3D.h"

class CMesh3D
{
public:
	CMesh3D(void) {clear();}
	CMesh3D(const char* filePath); //only stl supported currently
	CMesh3D(CArray3D<float>& values, CArray3D<Vec3D<float>>& normals, float threshold, float scale = 1.0f, float (*density)(Vec3D<float>&, Vec3D<float>*) = 0);
	//CMesh3D(float (*density)(Vec3D<float>&), Vec3D<float>& min, Vec3D<float>& max, int maxDivs, float threshold); //maxDivs = number of voxels in maximum dimension 
	//virtual ~CMesh(){};

	//to DC file!
	Vec3Df QEF(const std::vector<Vec3Df>& intersects, const std::vector<Vec3Df>& normals, const Vec3Df& min, const Vec3Df& max);
	//Vec3Df meanValueIntersect(const std::vector<Vec3Df>& points, const Vec3Df intersect, const int axis); //0=x, 1=y, 2=z

	void clear();
	bool load(const char* filePath); //stl
	bool save(const char* filePath); //stl or obj (color) //!< Save the current deformed mesh as an obj file to the path specified. Coloring is not supported yet. @param[in] filePath File path to save the obj file as. Creates or overwrites.

	void addTriangle(Vec3D<float>& p1, Vec3D<float>& p2, Vec3D<float>& p3); //assummed ccw order
	int triangleCount() {return (int)(triangles.size()/3);}
	int vertexCount() {return (int)(vertices.size()/3);}

	bool isInside(Vec3D<float>* point); //true if inside mesh, false
	float distanceFromSurface(Vec3D<float>* point, float maxDistance, Vec3D<float>* pNormalOut = 0); //returns "blended" distance if within maxDistance. positive for outside, negative for inside.

	void useFaceNormals(); // calc ? 
	void useVertexNormals(float seamAngleDegrees = 0); // seams between triangles less than seamAngleDegrees show as smooth

	Vec3D<float> meshMin() {if (boundsStale) updateBounds(); return boundsMin;}
	Vec3D<float> meshMax() {if (boundsStale) updateBounds(); return boundsMax;}
	Vec3D<float> meshSize() {if (boundsStale) updateBounds(); return boundsMax-boundsMin;}


	void translate(Vec3D<float> d); // translate geometry
	void scale(Vec3D<float> s); // scale geometry
	void rotate(Vec3D<float> ax, float a);
	//void rotX(float a);
	//void rotY(float a);
	//void rotZ(float a);

	void decimate();

	void glDraw(); //!< Executes openGL drawing commands to draw this mesh in an Open GL window if USE_OPEN_GL is defined.

protected:
//	Vec3Df vInterpLow(float iso, Vec3D<float> p1, Vec3D<float> p2, float valp1, float valp2, float (*density)(Vec3D<float>&, Vec3D<float>*), Vec3Df* pNormalOut, float maxError, int maxIter = 5);



	std::vector<float> vertices; //vx1, vy1, vz1, vx2, vy2, vz2, vx3, ...
//	std::vector<Vec3D<float>> vertices; //vx1, vy1, vz1, vx2, vy2, vz2, vx3, ...
	std::vector<float> vertexColors; //v1R, v1G, v1B, v2R, v2G, v2B, ... if size != 0, use all vertex colors. Otherwise triangle colors
	std::vector<float> vertexNormals; //t1Nx, t1Ny, t1Nz, t2Nx, t2Ny, t2Nz, ... if size != 0, use all vertex normals. Otherwise triangle normals

	std::vector<int> triangles; //t1v1, t1v2, t1v3, t2v1, t2v2, ... (ccw order)
	std::vector<float> triangleColors; //t1R, t1G, t1B, t2R, t2G, t2B, ... 
	std::vector<float> triangleNormals; //t1Nx, t1Ny, t1Nz, t2Nx, t2Ny, t2Nz, ... (needs updating with mesh deformation)

	std::vector<int> lines; //l1v1, l1v2, l2v1, l2v2, ...

	void meshChanged(); //call whenever geometry has changed (facets added or removed)

//	void weldVertices(float threshold = 1e-7, float angle = -1); //welds vertices that are nearby (within threshold) and from triangles less than angle (in radians)

private:
	bool normalsByVertex, colorsByVertex; //normals / colors drawn from vertices (vs by facet)
	float currentSeamAngle;

	bool vertexNormalsStale, vertexMergesStale, faceNormalsStale, boundsStale, slicerStale;

	void mergeVertices(float precision); //precision is 2^precision (max 10) divisions in each dimension to count as "close" enough to merge.
	void splitVerticesByAngle(float seamAngleDegrees);

	Vec3D<float> boundsMin, boundsMax; //bounds
	void updateBounds(void);
	
//	voxelizing stuff

//	~CMesh(void);
//
//	CMesh(CMesh& s);
//	CMesh& operator=(const CMesh& s);
//
//	void WriteXML(CXML_Rip* pXML, bool MeshOnly = false); //meshonly only store stl-equiavalent info (no color, normals, etc...)
//	bool ReadXML(CXML_Rip* pXML);
//
//	bool Exists(void) {if (Facets.size() != 0) return true; else return false;}
//	std::vector<CFacet> Facets;
//	std::vector<CVertex> Vertices;
//	std::vector<CLine> Lines;
//
//	Vec3D<> _CurBBMin, _CurBBMax; //cached bounding box values... (UpdateBoundingBox to update())
//
//	// file i/o
	bool loadSTL(std::string& filePath);

	bool saveSTL(std::string& filePath, bool binary = true) const;
	bool saveOBJ(std::string& filePath) const; //!< Save the current deformed mesh as an obj file to the path specified. Coloring is not supported yet. @param[in] filePath File path to save the obj file as. Creates or overwrites.

//
	bool loadBinarySTL(std::string filePath);
	bool loadAsciiSTL(std::string filePath);


//	bool DrawSmooth;
	void calcFaceNormals(); //called to update the face normals...
	void calcVertNormals(float seamAngleDegrees = 0); //called once for each new geometry (or after deformed...) (depends on face normals!!!)

	std::vector<int> TriLayer, TriLine; //array of all triangle indices that cross the current z layer, or y line
	std::vector<float> TriInts; //array of all intersection points at the current z height at the curernt Y value
	float _lastZ, _lastY, _lastPad; //height we calculated TriHeight, TriLine at
	void FillTriLayer(float z, float pad = 0.0f); //fills in TriLayer with all triangles that bridge this plane. returns true if re-calculated.
	void FillTriLine(float y, float z, float pad = 0.0); //fills in TriLine with all triangle the bridge the line in the layer. returns true if re-calculated.
	bool FillTriInts(float y, float z, float pad = 0.0f); //fills in TriLine with all triangle the bridge the line in the layer. returns true if re-calculated.
	bool FillCheckTriInts(float y, float z, float pad = 0.0f); //Keeps trying FillTriInts until valid results found


	enum IntersectionType {IT_INSIDE, IT_OUTSIDE, IT_EDGE};
	IntersectionType IntersectXRay(const int TriangleIndex, const float y, const float z, float& XIntersect) const;
	bool GetTriDist(const int TriangleIndex, const Vec3D<float>* pPointIn, float& UOut, float& VOut, Vec3D<float>& ToSurfPointOut) const; //gets distance of provided point to closest UV coordinate of within the triangle. returns true if sensible distance, otherwise false
	float GetTriArea(const int TriangleIndex);

//	int GetXIntersections(float z, float y, float* pIntersections, int NumtoCheck, int* pToCheck); //returns the number of intersections, stored in pIntersections
//	static bool InsideTri(Vec3D<>& p, Vec3D<>& v0, Vec3D<>& v1, Vec3D<>& v2);
//	static float Det(Vec3D<>& v0, Vec3D<>& v1, Vec3D<>& v2);
//	bool IntersectXRay(int triIndex, float y, float z, Vec3D<float>& p, float& pu, float& pv);




//#ifdef USE_OPEN_GL
//	void Draw(bool bModelhNormals = false, bool bShaded = true, bool bIngoreColors = false, bool bIgnoreNames = false); //requires OpenGL libs
//#endif
//
//	//add a facet
//	void AddFacet(const Vec3D<>& v1, const Vec3D<>& v2, const Vec3D<>& v3, bool QuickAdd = false); //adds a facet, checks vertex list for existing vertices... (should be called with vertices in CCW for proper normal calculation!
//	void AddFacet(const Vec3D<>& v1, const Vec3D<>& v2, const Vec3D<>& v3, const CColor& Col1, const CColor& Col2, const CColor& Col3, bool QuickAdd = false); //adds a facet... with color info
//	void AddQuadFacet(const Vec3D<>& v1, const Vec3D<>& v2, const Vec3D<>& v3, const Vec3D<>& v4) {AddFacet(v1, v2, v3); AddFacet(v3, v4, v1);}; //Vertices should be CCW from outside
//
//	// clear/reset the list of trianges
//	void Clear() { Facets.clear(); Vertices.clear(); Lines.clear();}
//	
//	void ComputeBoundingBox(Vec3D<>& pmin, Vec3D<>& pmax);
//	void UpdateBoundingBox(void);
//	Vec3D<> GetBBMin(void) {return _CurBBMin;}
//	Vec3D<> GetBBMax(void) {return _CurBBMax;}
//	Vec3D<> GetBBSize(void) {return _CurBBMax - _CurBBMin;}
//
//
//	//manipulation...
//	void Scale(Vec3D<> d);
//	void Translate(Vec3D<> d);
//	void Rotate(Vec3D<> ax, vfloat a);
//	void RotX(vfloat a);
//	void RotY(vfloat a);
//	void RotZ(vfloat a);
//
//	//voxelizing stuff!
//	void MeshChanged(void); //invalidates all cached voxelizing info!
//
//	bool IsInside(Vec3D<>* Point);
//	std::vector<int> TriLayer; //array of all triangle indices that cross the current z height
//	std::vector<vfloat> TriLine; //array of all intersection points at the current z height at the curernt Y vale
//	vfloat _TriLayerZ, _TriLineY; //height we calculated TriHeight, TriLine at
//	void FillTriLayer(vfloat z); //fills in TriLayer with all triangles that bridge this plane
//	void FillTriLine(vfloat y, vfloat z); //fills in TriLine with all triangle the bridge the line in the layer
//
//
//	int GetXIntersections(vfloat z, vfloat y, vfloat* pIntersections, int NumtoCheck, int* pToCheck); //returns the number of intersections, stored in pIntersections
//	
//
//
//	static bool InsideTri(Vec3D<>& p, Vec3D<>& v0, Vec3D<>& v1, Vec3D<>& v2);
//	static vfloat Det(Vec3D<>& v0, Vec3D<>& v1, Vec3D<>& v2);
//	bool IntersectXRay(CFacet* pFacet, vfloat y, vfloat z, Vec3D<>& p, vfloat& pu, vfloat& pv);
//
//	void WeldClose(float Distance); //welds vertices that are nearby (within Distance). Removes deleted triangles...
//	void RemoveDupLines(void);
//
//protected:
//	bool LoadBinarySTL(std::string filename);
//	bool LoadAsciiSTL(std::string filename);
};
#endif //MESH3D_H
