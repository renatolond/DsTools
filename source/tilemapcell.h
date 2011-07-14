#ifndef TILEMAPCELL_H
#define TILEMAPCELL_H

#include "vector2.h"
//#include "aabb.h"
//#include "circle.h"
//#include "all_gfx.h"

#define SQRT2 1.414214E+000
#define SQRT5 2.236068E+000

typedef int tTileType;

class cAABB;

namespace TileEnum
{
enum TileID
{
  empty,
  full,

  _45degPN,
  _45degNN,
  _45degNP,
  _45degPP,

  concavePN,
  concaveNN,
  concaveNP,
  concavePP,

  convexPN,
  convexNN,
  convexNP,
  convexPP,

  _22degPNs,
  _22degNNs,
  _22degNPs,
  _22degPPs,

  _22degPNb,
  _22degNNb,
  _22degNPb,
  _22degPPb,

  _67degPNs,
  _67degNNs,
  _67degNPs,
  _67degPPs,

  _67degPNb,
  _67degNNb,
  _67degNPb,
  _67degPPb,

  halfD,
  halfR,
  halfU,
  halfL

};
}

namespace CTypeEnum
{
enum CType
{
  _empty = TileEnum::empty,
  _full = TileEnum::full,
  _45deg = TileEnum::_45degPN,
  concave = TileEnum::concavePN,
  convex = TileEnum::convexPN,
  _22degs = TileEnum::_22degPNs,
  _22degb = TileEnum::_22degPNb,
  _67degs = TileEnum::_67degPNs,
  _67degb = TileEnum::_67degPNb,
  half = TileEnum::halfD
};
}

class cTileMapCell
{
  int signx;
  int signy;
  double sx;
  double sy;

  TileEnum::TileID id;
  CTypeEnum::CType ctype;
  //    SpriteController s;
public:
  Vector2 pos;
  tTileType xw;
  tTileType yw;

  cTileMapCell();
  cTileMapCell(tTileType x, tTileType y, tTileType xW, tTileType yW);
  void SetState(TileEnum::TileID ID);
  void Clear();
  void UpdateType();
  void Draw();
  void projAABB(tTileType x, tTileType y, cAABB& aabb);
  void projAABBFull(tTileType x, tTileType y, cAABB& aabb);
//  void projAABB45deg(tTileType x, tTileType y, cAABB& aabb);
//  void projAABBConcave(tTileType x, tTileType y, cAABB& aabb);
//  void projAABBConvex(tTileType x, tTileType y, cAABB& aabb);
//  void projAABB22degS(tTileType x, tTileType y, cAABB& aabb);
//  void projAABB22degB(tTileType x, tTileType y, cAABB& aabb);
//  void projAABB67degS(tTileType x, tTileType y, cAABB& aabb);
//  void projAABB67degB(tTileType x, tTileType y, cAABB& aabb);
//  void projAABBHalf(tTileType x, tTileType y, cAABB& aabb);
//  void projCircle(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircleFull(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircle45deg(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircleConcave(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircleConvex(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircle22degS(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircle22degB(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircle67degS(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircle67degB(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
//  void projCircleHalf(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle);
  tTileType minX();
  tTileType maxX();
  tTileType minY();
  tTileType maxY();
};

#endif // TILEMAPCELL_H
