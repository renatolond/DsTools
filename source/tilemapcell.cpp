#include "tilemapcell.h"

#include "aabb.h"

cTileMapCell::cTileMapCell()
{

}


cTileMapCell::cTileMapCell(tTileType x, tTileType y, tTileType xW, tTileType yW)
{
  pos = Vector2(x, y);
  xw = xW;
  yw = yW;
  id = TileEnum::empty;
  ctype = CTypeEnum::_empty;
}

void cTileMapCell::projAABBFull(tTileType x, tTileType y, cAABB& aabb)
{
  double temp;
  temp = sqrt(x*x + y*y);
  aabb.report_collision_vs_world(x, y, x/temp, y/temp);
}

//void cTileMapCell::projAABB45deg(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType ox, oy;
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);
//  ox = aabb.getPos().x - signx * aabbxw - pos.x;
//  oy = aabb.getPos().y - signy * aabbyw - pos.y;

//  tTileType dp = ox * sx + oy * sy;
//  if ( dp < 0 )
//  {
//    tTileType ssx, ssy;
//    ssx = sx*-dp;
//    ssy = sy*-dp;

//    tTileType lenN, lenP;
//    lenN = sqrt(ssx*ssx + ssy*ssy);
//    lenP = sqrt(x*x + y*y);

//    if ( lenP < lenN )
//    {
//      aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//    }
//    else
//    {
//      aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//    }
//  }
//}

//void cTileMapCell::projAABBConcave(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType ox, oy, twid;
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);
//  ox = pos.x + signx * xw - (aabb.getPos().x - signx * aabbxw);
//  oy = pos.y + signy * yw - (aabb.getPos().y - signy * aabbyw);
//  twid = xw * 2;

//  tTileType len = sqrt(ox*ox+oy*oy);
//  tTileType pen = len - twid;
//  if ( pen > 0 )
//  {
//    tTileType lenP = sqrt(x*x + y*y);

//    if ( lenP < pen )
//    {
//      aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//    }
//    else
//    {
//      ox = ox / len;
//      oy = oy / len;
//      aabb.ReportCollisionVsWorld(ox * pen, oy * pen, ox, oy);
//    }
//  }
//}

//void cTileMapCell::projAABBConvex(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType ox, oy, twid;
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);
//  ox = aabb.getPos().x - signx * aabbxw - (pos.x - signx * xw);
//  oy = aabb.getPos().y - signy * aabbyw - (pos.y - signy * yw);
//  twid = xw * 2;

//  tTileType len = sqrt(ox*ox+oy*oy);
//  tTileType pen = twid - len;
//  if ( signx * ox < 0 || signy * oy < 0 )
//  {
//    tTileType lenP = sqrt(x*x + y*y);
//    aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//  }
//  else if ( pen > 0 )
//  {
//    ox = ox / len;
//    oy = oy / len;
//    aabb.ReportCollisionVsWorld(ox * pen, oy * pen, ox, oy);
//  }
//}

//void cTileMapCell::projAABB22degS(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType py;
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);

//  py = aabb.getPos().y - signy * aabbyw;

//  tTileType cy = pos.y - py;

//  if ( cy*signy > 0 )
//  {
//    tTileType ox, oy;
//    ox = aabb.getPos().x - signx * aabbxw - (pos.x + signx*xw);
//    oy = aabb.getPos().y - signy * aabbyw - (pos.y - signy*yw);

//    tTileType dp = ox * sx + oy * sy;
//    if ( dp < 0 )
//    {
//      tTileType ssx, ssy;
//      ssx = sx*-dp;
//      ssy = sy*-dp;

//      tTileType lenN, lenP;
//      lenN = sqrt(ssx*ssx + ssy*ssy);
//      lenP = sqrt(x*x + y*y);

//      tTileType ay = fabs(cy);

//      if ( lenP < lenN )
//      {
//        if ( ay < lenP )
//          aabb.ReportCollisionVsWorld(0, cy, 0, cy/ay);
//        else
//          aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//      }
//      else
//      {
//        if ( ay < lenN )
//          aabb.ReportCollisionVsWorld(0, cy, 0, cy/ay);
//        else
//          aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//      }
//    }
//  }
//}

//void cTileMapCell::projAABB22degB(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);

//  tTileType ox, oy;
//  ox = aabb.getPos().x - signx * aabbxw - (pos.x - signx*xw);
//  oy = aabb.getPos().y - signy * aabbyw - (pos.y + signy*yw);

//  tTileType dp = ox * sx + oy * sy;
//  if ( dp < 0 )
//  {
//    tTileType ssx, ssy;
//    ssx = sx*-dp;
//    ssy = sy*-dp;

//    tTileType lenN, lenP;
//    lenN = sqrt(ssx*ssx + ssy*ssy);
//    lenP = sqrt(x*x + y*y);


//    if ( lenP < lenN )
//    {
//      aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//    }
//    else
//    {
//      aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//    }
//  }
//}

//void cTileMapCell::projAABB67degS(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType px;
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);

//  px = aabb.getPos().x - signx * aabbxw;

//  tTileType cx = pos.x - px;

//  if ( cx*signx > 0 )
//  {
//    tTileType ox, oy;
//    ox = aabb.getPos().x - signx * aabbxw - (pos.x - signx*xw);
//    oy = aabb.getPos().y - signy * aabbyw - (pos.y + signy*yw);

//    tTileType dp = ox * sx + oy * sy;
//    if ( dp < 0 )
//    {
//      tTileType ssx, ssy;
//      ssx = sx*-dp;
//      ssy = sy*-dp;

//      tTileType lenN, lenP;
//      lenN = sqrt(ssx*ssx + ssy*ssy);
//      lenP = sqrt(x*x + y*y);

//      tTileType ax = fabs(cx);

//      if ( lenP < lenN )
//      {
//        if ( ax < lenP )
//          aabb.ReportCollisionVsWorld(cx, 0, cx/ax, 0);
//        else
//          aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//      }
//      else
//      {
//        if ( ax < lenN )
//          aabb.ReportCollisionVsWorld(cx, 0, cx/ax, 0);
//        else
//          aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//      }
//    }
//  }
//}

//void cTileMapCell::projAABB67degB(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);

//  tTileType ox, oy;
//  ox = aabb.getPos().x - signx * aabbxw - (pos.x + signx*xw);
//  oy = aabb.getPos().y - signy * aabbyw - (pos.y - signy*yw);

//  tTileType dp = ox * sx + oy * sy;
//  if ( dp < 0 )
//  {
//    tTileType ssx, ssy;
//    ssx = sx*-dp;
//    ssy = sy*-dp;

//    tTileType lenN, lenP;
//    lenN = sqrt(ssx*ssx + ssy*ssy);
//    lenP = sqrt(x*x + y*y);


//    if ( lenP < lenN )
//    {
//      aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//    }
//    else
//    {
//      aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//    }
//  }
//}

//void cTileMapCell::projAABBHalf(tTileType x, tTileType y, cAABB& aabb)
//{
//  tTileType aabbxw, aabbyw;
//  aabb.getExt(aabbxw, aabbyw);

//  tTileType ox, oy;
//  ox = aabb.getPos().x - signx * aabbxw - pos.x;
//  oy = aabb.getPos().y - signy * aabbyw - pos.y;

//  tTileType dp = ox * sx + oy * sy;
//  if ( dp < 0 )
//  {
//    tTileType ssx, ssy;
//    ssx = sx*-dp;
//    ssy = sy*-dp;

//    tTileType lenN, lenP;
//    lenN = sqrt(ssx*ssx + ssy*ssy);
//    lenP = sqrt(x*x + y*y);


//    if ( lenP < lenN )
//    {
//      aabb.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//    }
//    else
//    {
//      aabb.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//    }
//  }
//}


void cTileMapCell::projAABB(tTileType x, tTileType y, cAABB& aabb)
{
  if ( ctype != CTypeEnum::_empty )
  {
    //char message[1024];
    //sprintf(message,"Collided against %d,%d",(int)pos.x, (int)pos.y);
    //nocashMessage(message);
  }

  if ( ctype == CTypeEnum::_full )
    projAABBFull(x, y, aabb);
//  if ( ctype == CTypeEnum::_45deg )
//    projAABB45deg(x, y, aabb);
//  if ( ctype == CTypeEnum::concave )
//    projAABBConcave(x, y, aabb);
//  if ( ctype == CTypeEnum::convex )
//    projAABBConvex(x, y, aabb);
//  if ( ctype == CTypeEnum::_22degs )
//    projAABB22degS(x, y, aabb);
//  if ( ctype == CTypeEnum::_22degb )
//    projAABB22degB(x, y, aabb);
//  if ( ctype == CTypeEnum::_67degs )
//    projAABB67degS(x, y, aabb);
//  if ( ctype == CTypeEnum::_67degb )
//    projAABB67degB(x, y, aabb);
//  if ( ctype == CTypeEnum::half )
//    projAABBHalf(x, y, aabb);
}

//void cTileMapCell::projCircle(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle)
//{
//  if ( ctype == CTypeEnum::_full )
//    projCircleFull(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::_45deg )
//    projCircle45deg(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::concave )
//    projCircleConcave(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::convex )
//    projCircleConvex(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::_22degs )
//    projCircle22degS(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::_22degb )
//    projCircle22degB(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::_67degs )
//    projCircle67degS(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::_67degb )
//    projCircle67degB(x, y, oh, ov, circle);
//  if ( ctype == CTypeEnum::half )
//    projCircleHalf(x, y, oh, ov, circle);
//}

//void cTileMapCell::projCircleFull(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T>& circle)
//{
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( x < y )
//      {
//        tTileType dx = circle.getPos().x - pos.x;
//        if ( dx < 0 )
//          circle.ReportCollisionVsWorld(-x, 0, -1, 0);
//        else
//          circle.ReportCollisionVsWorld(x, 0, 1, 0);
//      }
//      else
//      {
//        tTileType dy = circle.getPos().y - pos.y;
//        if ( dy < 0 )
//          circle.ReportCollisionVsWorld(0, -y, 0, -1);
//        else
//          circle.ReportCollisionVsWorld(0, y, 0, 1);
//      }
//    }
//    else
//      circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//      circle.ReportCollisionVsWorld(x * oh, 0, oh, 0);
//    else
//    {
//      tTileType vx, vy, dx, dy, len, pen, r;
//      vx = pos.x + oh * xw;
//      vy = pos.y + ov * yw;
//      dx = circle.getPos().x - vx;
//      dy = circle.getPos().y - vy;
//      len = sqrt(dx*dx + dy*dy);
//      circle.getExt(r, r);
//      pen = r - len;

//      if ( pen > 0 )
//      {
//        if ( fabs(len) < eps )
//        {
//          dx = oh / SQRT2;
//          dy = oh / SQRT2;
//        }
//        else
//        {
//          dx = dx / len;
//          dy = dy / len;
//        }

//        circle.ReportCollisionVsWorld(dx * pen, dy * pen, dx, dy);
//      }
//    }
//  }
//}

//void cTileMapCell::projCircle45deg(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType r;
//      tTileType ox, oy;
//      circle.getExt(r, r);
//      ox = circle.getPos().x - sx * r - pos.x;
//      oy = circle.getPos().y - sy * r - pos.y;

//      tTileType dp = ox * sx + oy * sy;

//      if ( dp < 0 )
//      {
//        tTileType ssx, ssy;
//        tTileType lenP, lenN;
//        ssx = sx * -dp;
//        ssy = sy * -dp;
//        if ( x < y )
//        {
//          lenP = x;
//          y = 0;
//          if ( circle.getPos().x - pos.x < 0 )
//            x *= -1;
//        }
//        else
//        {
//          lenP = y;
//          x = 0;
//          if ( circle.getPos().y - pos.y < 0 )
//            y *= -1;
//        }
//        lenN = sqrt(ssx*ssx + ssy*ssy);
//        if ( lenP < lenN )
//          circle.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//        else
//          circle.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//      }
//    }
//    else
//    {
//      if ( signy * ov < 0 )
//        circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//      else
//      {
//        tTileType r;
//        tTileType ox, oy;
//        tTileType perp;
//        circle.getExt(r, r);

//        ox = circle.getPos().x - ( pos.x - signx * xw );
//        oy = circle.getPos().y - ( pos.y + ov * yw );

//        perp = ox * -sy + oy * sx;
//        if ( perp * signx * signy > 0 )
//        {
//          tTileType len = sqrt(ox*ox + oy*oy);
//          tTileType pen = r - len;
//          if ( pen > 0 )
//          {
//            ox /= len;
//            oy /= len;
//            circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//          }
//        }
//        else
//        {
//          tTileType dp = ox * sx + oy * sy;
//          tTileType pen = r - fabs(dp);
//          if ( pen > 0 )
//          {
//            circle.ReportCollisionVsWorld(sx * pen, sy * pen, sx, sy);
//          }
//        }
//      }
//    }
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( signx * oh < 0 )
//      {
//        circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//      }
//      else
//      {
//        tTileType ox, oy;
//        tTileType perp;
//        tTileType r;
//        circle.getExt(r, r);

//        ox = circle.getPos().x - ( pos.x + oh*xw );
//        oy = circle.getPos().y - ( pos.y - signy*yw );
//        perp = ox * -sy + oy * sy;
//        if ( perp * signx * signy < 0 )
//        {
//          tTileType len, pen;
//          len = sqrt(ox*ox + oy*oy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            ox /= len;
//            oy /= len;
//            circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//          }
//        }
//        else
//        {
//          tTileType dp = ox*sx + oy*sy;
//          tTileType pen = r - fabs(dp);
//          if ( pen > 0 )
//            circle.ReportCollisionVsWorld(sx*pen, sy*pen, sx, sy);
//        }
//      }
//    }
//    else if ( !(signx * oh + signy * ov > 0) )
//    {
//      tTileType dx, dy, vx, vy, len, pen, r;

//      circle.getExt(r, r);

//      vx = pos.x + oh * xw;
//      vy = pos.y + ov * yw;
//      dx = circle.getPos().x - vx;
//      dy = circle.getPos().y - vy;
//      len = sqrt(dx*dx + dy*dy);
//      pen = r - len;

//      if ( pen > 0 )
//      {
//        if ( fabs(len) < eps )
//        {
//          dx = oh / SQRT2;
//          dy = ov / SQRT2;
//        }
//        else
//        {
//          dx = dx / len;
//          dy = dy / len;
//        }

//        circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//      }
//    }
//  }
//}

//void cTileMapCell::projCircleConcave(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType ox, oy;
//      ox = pos.x + signx * xw - circle.getPos().x;
//      oy = pos.y + signy * yw - circle.getPos().y;
//      tTileType trad = xw * 2;
//      tTileType len = sqrt(ox*ox+oy*oy);
//      tTileType r;
//      circle.getExt(r, r);
//      tTileType pen = len + r - trad;
//      if ( pen > 0 )
//      {
//        tTileType lenP;

//        if ( x < y )
//        {
//          lenP = x;
//          y = 0;
//          if ( circle.getPos().x - pos.x < 0 )
//            x *= -1;
//        }
//        else
//        {
//          lenP = y;
//          x = 0;
//          if ( circle.getPos().y - pos.y < 0 )
//            y *= -1;
//        }

//        if ( lenP < pen )
//          circle.ReportCollisionVsWorld(x, y, x / lenP, y / lenP);
//        else
//        {
//          ox /= len;
//          oy /= len;
//          circle.ReportCollisionVsWorld(ox * pen, oy * pen, ox, oy);
//        }
//      }
//    }
//    else
//    {
//      if ( signy * ov < 0 )
//        circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//      else
//      {
//        tTileType vx, vy, dx, dy, len, pen;
//        tTileType r;
//        circle.getExt(r, r);
//        vx = pos.x - signx * xw;
//        vy = pos.y + ov * yw;
//        dx = circle.getPos().x - vx;
//        dy = circle.getPos().y - vy;
//        len = sqrt(dx*dx + dy*dy);
//        pen = r - len;
//        if ( pen > 0 )
//        {
//          if ( fabs(len) < eps )
//          {
//            dx = 0;
//            dy = ov;
//          }
//          else
//          {
//            dx /= len;
//            dy /= len;
//          }
//          circle.ReportCollisionVsWorld(dx * pen, dy * pen, dx, dy);
//        }
//      }
//    }
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( signx * oh < 0 )
//      {
//        circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//      }
//      else
//      {
//        tTileType vx, vy, dx, dy , len, pen;
//        tTileType r;
//        circle.getExt(r, r);
//        vx = pos.x + oh * xw;
//        vy = pos.y - signy * yw;
//        dx = circle.getPos().x - vx;
//        dy = circle.getPos().y - vy;
//        len = sqrt(dx*dx + dy*dy);
//        pen = r - len;
//        if ( pen > 0 )
//        {
//          if ( fabs(len) < eps )
//          {
//            dx = oh;
//            dy = 0;
//          }
//          else
//          {
//            dx /= len;
//            dy /= len;
//          }
//          circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//        }
//      }
//    }
//    else if ( !(signx * oh + signy * ov > 0) )
//    {
//      tTileType vx, vy, dx, dy , len, pen;
//      tTileType r;
//      circle.getExt(r, r);
//      vx = pos.x + oh * xw;
//      vy = pos.y + ov * yw;
//      dx = circle.getPos().x - vx;
//      dy = circle.getPos().y - vy;
//      len = sqrt(dx*dx + dy*dy);
//      pen = r - len;
//      if ( pen > 0 )
//      {
//        if ( fabs(len) < eps )
//        {
//          dx = oh/SQRT2;
//          dy = ov/SQRT2;
//        }
//        else
//        {
//          dx /= len;
//          dy /= len;
//        }
//        circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//      }
//    }
//  }
//}

//void cTileMapCell::projCircleConvex(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType ox, oy, trad, len, pen;
//      tTileType r;
//      circle.getExt(r, r);

//      ox = circle.getPos().x - ( pos.x - signx * xw );
//      oy = circle.getPos().y - ( pos.y - signy * yw );
//      trad = xw * 2;
//      len = sqrt(ox*ox + oy*oy);
//      pen = trad + r - len;
//      if ( pen > 0 )
//      {
//        tTileType lenP;
//        if ( x < y )
//        {
//          lenP = x;
//          y = 0;
//          if ( circle.getPos().x - pos.x < 0 )
//            x *= -1;
//        }
//        else
//        {
//          lenP = y;
//          x = 0;
//          if ( circle.getPos().y - pos.y < 0 )
//            y *= -1;
//        }

//        if ( lenP < pen )
//          circle.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//        else
//        {
//          ox /= len;
//          oy /= len;
//          circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//        }
//      }
//    }
//    else
//    {
//      if ( signy * ov < 0 )
//        circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//      else
//      {
//        tTileType ox, oy, trad, len, pen;
//        tTileType r;
//        circle.getExt(r, r);

//        ox = circle.getPos().x - ( pos.x - signx * xw );
//        oy = circle.getPos().y - ( pos.y - signy * yw );
//        trad = xw * 2;
//        len = sqrt(ox*ox + oy*oy);
//        pen = trad + r - len;
//        if ( pen > 0 )
//        {
//          ox /= len;
//          oy /= len;
//          circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//        }
//      }
//    }
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( signx * oh < 0 )
//      {
//        circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//      }
//      else
//      {
//        tTileType ox, oy, trad, len, pen;
//        tTileType r;
//        circle.getExt(r, r);

//        ox = circle.getPos().x - ( pos.x - signx * xw );
//        oy = circle.getPos().y - ( pos.y - signy * yw );
//        trad = xw * 2;
//        len = sqrt(ox*ox + oy*oy);
//        pen = trad + r - len;
//        if ( pen > 0 )
//        {
//          ox /= len;
//          oy /= len;
//          circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//        }

//      }
//    }
//    else
//    {
//      if ( signx * oh + signy * ov > 0 )
//      {
//        tTileType ox, oy, trad, len, pen;
//        tTileType r;
//        circle.getExt(r, r);

//        ox = circle.getPos().x - ( pos.x - signx * xw );
//        oy = circle.getPos().y - ( pos.y - signy * yw );
//        trad = xw * 2;
//        len = sqrt(ox*ox + oy*oy);
//        pen = trad + r - len;
//        if ( pen > 0 )
//        {
//          ox /= len;
//          oy /= len;
//          circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//        }
//      }
//      else
//      {
//        tTileType vx, vy, len, pen, dx, dy;
//        tTileType r;
//        circle.getExt(r, r);

//        vx = pos.x + oh * xw;
//        vy = pos.y + ov * yw;
//        dx = circle.getPos().x - vx;
//        dy = circle.getPos().y - vy;
//        len = sqrt(dx*dx + dy*dy);
//        pen = r - len;
//        if ( pen > 0 )
//        {
//          if ( fabs(len) < eps )
//          {
//            dx = oh / SQRT2;
//            dy = ov / SQRT2;
//          }
//          else
//          {
//            dx /= len;
//            dy /= len;
//          }
//          circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//        }
//      }
//    }
//  }
//}

//void cTileMapCell::projCircle22degS(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( signy * ov > 0 )
//    return;
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType r;
//      circle.getExt(r, r);
//      tTileType ox, oy, perp;
//      ox = circle.getPos().x - (pos.x - signx * xw);
//      oy = circle.getPos().y - pos.y;
//      perp = ox * -sy + oy * sx;
//      if ( perp * signx * signy > 0 )
//      {
//        tTileType len, pen;
//        len = sqrt(ox*ox + oy*oy);
//        pen = r - len;
//        if ( pen > 0 )
//        {
//          ox /= len;
//          oy /= len;
//          circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//        }
//      }
//      else
//      {
//        tTileType dp;

//        ox -= r*sx;
//        oy -= r*sy;
//        dp = ox * sx + oy * sy;
//        if ( dp < 0 )
//        {
//          tTileType ssx, ssy, lenN, lenP;
//          ssx = sx*-dp;
//          ssy = sy*-dp;
//          lenN = sqrt(ssx*ssx+ssy*ssy);
//          if ( x < y )
//          {
//            lenP = x;
//            y = 0;
//            if ( circle.getPos().x - pos.x < 0 )
//              x *= -1;
//          }
//          else
//          {
//            lenP = y;
//            x = 0;
//            if ( circle.getPos().y - pos.y < 0 )
//              y *= -1;
//          }

//          if ( lenP < lenN )
//            circle.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//          else
//            circle.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//        }
//      }
//    }
//    else
//      circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( signx*oh < 0 )
//      {
//        tTileType vx, vy, dx, dy;
//        vx = pos.x - signx * xw;
//        vy = pos.y;
//        dx = circle.getPos().x - vx;
//        dy = circle.getPos().y - vy;

//        if ( dy * signy < 0 )
//          circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//        else
//        {
//          tTileType len, pen;
//          tTileType r;
//          circle.getExt(r, r);
//          len = sqrt(dx*dx + dy*dy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            if ( fabs(len) < eps )
//            {
//              dx = oh/SQRT2;
//              dy = oh/SQRT2;
//            }
//            else
//            {
//              dx /= len;
//              dy /= len;
//            }
//            circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//          }
//        }
//      }
//      else
//      {
//        tTileType ox, oy, perp;
//        tTileType r;
//        circle.getExt(r, r);
//        ox = circle.getPos().x - (pos.x + oh*xw);
//        oy = circle.getPos().y - (pos.y - signy*yw);
//        perp = ox * -sy + oy * sx;
//        if ( perp * signx * signy < 0 )
//        {
//          tTileType len, pen;
//          len = sqrt(ox*ox + oy*oy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            ox /= len;
//            oy /= len;
//            circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//          }
//        }
//        else
//        {
//          tTileType dp, pen;
//          dp = ox*sx + oy*sy;
//          pen = r - fabs(dp);
//          if ( pen > 0 )
//            circle.ReportCollisionVsWorld(sx*pen, sy*pen, sx, sy);
//        }
//      }
//    }
//    else
//    {
//      tTileType vx, vy, dx, dy, len, pen;
//      tTileType r;
//      circle.getExt(r, r);
//      vx = pos.x + oh * xw;
//      vy = pos.y + ov * yw;
//      dx = circle.getPos().x - vx;
//      dy = circle.getPos().y - vy;
//      len = sqrt(dx*dx+dy*dy);
//      pen = r - len;
//      if ( pen > 0 )
//      {
//        if ( fabs(len) < eps )
//        {
//          dx = oh / SQRT2;
//          dy = ov / SQRT2;
//        }
//        else
//        {
//          dx /= len;
//          dy /= len;
//        }
//        circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//      }
//    }
//  }
//}

//void cTileMapCell::projCircle22degB(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType ox, oy, dp;
//      tTileType r;
//      circle.getExt(r, r);
//      ox = circle.getPos().x - sx * r - (pos.x - signx * xw);
//      oy = circle.getPos().y - sy * r - (pos.y + signy * yw);
//      dp = ox * sx + oy * sy;
//      if ( dp < 0 )
//      {
//        tTileType ssx, ssy, lenN, lenP;
//        ssx = sx * -dp;
//        ssy = sy * -dp;
//        lenN = sqrt(ssx*ssx + ssy*ssy);
//        if ( x < y )
//        {
//          lenP = x;
//          y = 0;
//          if ( circle.getPos().x - pos.x < 0 )
//            x *= -1;
//        }
//        else
//        {
//          lenP = y;
//          x = 0;
//          if ( circle.getPos().y - pos.y < 0 )
//            y *= -1;
//        }

//        if ( lenP < lenN )
//          circle.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//        else
//          circle.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//      }
//    }
//    else
//    {
//      if ( signy * ov < 0 )
//        circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//      else
//      {
//        tTileType ox, oy, perp;
//        tTileType r;
//        circle.getExt(r, r);
//        ox = circle.getPos().x - (pos.x - signx*xw);
//        oy = circle.getPos().y - (pos.y + signy*yw);
//        perp = ox * -sy + oy * sx;
//        if ( perp * signx * signy > 0 )
//        {
//          tTileType len, pen;
//          len = sqrt(ox*ox+oy*oy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            ox /= len;
//            oy /= len;
//            circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//          }
//        }
//        else
//        {
//          tTileType dp = ox * sx + oy * sy;
//          tTileType pen = r - fabs(dp);
//          if ( pen > 0 )
//            circle.ReportCollisionVsWorld(sx*pen, sy*pen, sx, sy);
//        }

//      }
//    }
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( signx * oh < 0 )
//        circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//      else
//      {
//        tTileType r;
//        circle.getExt(r, r);
//        tTileType ox, oy;
//        ox = circle.getPos().x - (pos.x + signx*xw);
//        oy = circle.getPos().y - pos.y;
//        if ( signy * oy < 0 )
//          circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//        else
//        {
//          tTileType perp = ox * -sy + oy * sx;
//          if ( perp * signx * signy < 0 )
//          {
//            tTileType len, pen;
//            len = sqrt(ox*ox + oy*oy);
//            pen = r - len;
//            if ( pen > 0 )
//            {
//              ox /= len;
//              oy /= len;
//              circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//            }
//          }
//          else
//          {
//            tTileType dp, pen;
//            dp = ox*sx + oy*sy;
//            pen = r - fabs(dp);
//            if ( pen > 0 )
//              circle.ReportCollisionVsWorld(sx*pen, sy*pen, sx, sy);
//          }
//        }
//      }
//    }
//    else
//    {
//      tTileType r;
//      circle.getExt(r,r);
//      if ( signx * oh + signy * ov > 0)
//      {
//        tTileType ox, oy, dp;
//        ox = circle.getPos().x - sx*r - (pos.x - signx*xw);
//        oy = circle.getPos().y - sy*r - (pos.y + signy*yw);
//        dp = ox*sx + oy*sy;
//        if ( dp < 0 )
//          circle.ReportCollisionVsWorld(-sx*dp, -sy*dp, sx, sy);
//      }
//      else
//      {
//        tTileType vx, vy, dx, dy, len, pen;
//        vx = pos.x - oh*xw;
//        vy = pos.y - ov*yw;
//        dx = circle.getPos().x - vx;
//        dy = circle.getPos().y - vy;
//        len = sqrt(dx*dx + dy*dy);
//        pen = r - len;
//        if ( pen > 0 )
//        {
//          if ( fabs(len) < eps )
//          {
//            dx = oh / SQRT2;
//            dy = ov / SQRT2;
//          }
//          else
//          {
//            dx /= len;
//            dy /= len;
//          }
//          circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//        }
//      }
//    }
//  }
//}

//void cTileMapCell::projCircle67degS(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( signx * oh > 0 )
//    return;
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType r;
//      circle.getExt(r, r);
//      tTileType ox, oy, perp;
//      ox = circle.getPos().x - pos.x;
//      oy = circle.getPos().y - (pos.y - signy*xw);
//      perp = ox * -sy + oy * sx;
//      if ( perp * signx * signy < 0 )
//      {
//        tTileType len, pen;
//        len = sqrt(ox*ox + oy*oy);
//        pen = r - len;
//        if ( pen > 0 )
//        {
//          ox /= len;
//          oy /= len;
//          circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//        }
//      }
//      else
//      {
//        tTileType dp;

//        ox -= r*sx;
//        oy -= r*sy;
//        dp = ox * sx + oy * sy;
//        if ( dp < 0 )
//        {
//          tTileType ssx, ssy, lenN, lenP;
//          ssx = sx*-dp;
//          ssy = sy*-dp;
//          lenN = sqrt(ssx*ssx+ssy*ssy);
//          if ( x < y )
//          {
//            lenP = x;
//            y = 0;
//            if ( circle.getPos().x - pos.x < 0 )
//              x *= -1;
//          }
//          else
//          {
//            lenP = y;
//            x = 0;
//            if ( circle.getPos().y - pos.y < 0 )
//              y *= -1;
//          }

//          if ( lenP < lenN )
//            circle.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//          else
//            circle.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//        }
//      }
//    }
//    else
//    {
//      if ( signy*ov < 0 )
//      {
//        tTileType vx, vy, dx, dy;
//        vx = pos.x;
//        vy = pos.y - signy * yw;
//        dx = circle.getPos().x - vx;
//        dy = circle.getPos().y - vy;

//        if ( dy * signy < 0 )
//          circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//        else
//        {
//          tTileType len, pen;
//          tTileType r;
//          circle.getExt(r, r);
//          len = sqrt(dx*dx + dy*dy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            if ( fabs(len) < eps )
//            {
//              dx = oh/SQRT2;
//              dy = oh/SQRT2;
//            }
//            else
//            {
//              dx /= len;
//              dy /= len;
//            }
//            circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//          }
//        }
//      }
//      else
//      {
//        tTileType ox, oy, perp;
//        tTileType r;
//        circle.getExt(r, r);
//        ox = circle.getPos().x - (pos.x - signx*xw);
//        oy = circle.getPos().y - (pos.y + ov*yw);
//        perp = ox * -sy + oy * sx;
//        if ( perp * signx * signy > 0 )
//        {
//          tTileType len, pen;
//          len = sqrt(ox*ox + oy*oy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            ox /= len;
//            oy /= len;
//            circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//          }
//        }
//        else
//        {
//          tTileType dp, pen;
//          dp = ox*sx + oy*sy;
//          pen = r - fabs(dp);
//          if ( pen > 0 )
//            circle.ReportCollisionVsWorld(sx*pen, sy*pen, sx, sy);
//        }
//      }
//    }
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//      circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//    else
//    {
//      tTileType vx, vy, dx, dy, len, pen;
//      tTileType r;
//      circle.getExt(r, r);
//      vx = pos.x + oh * xw;
//      vy = pos.y + ov * yw;
//      dx = circle.getPos().x - vx;
//      dy = circle.getPos().y - vy;
//      len = sqrt(dx*dx+dy*dy);
//      pen = r - len;
//      if ( pen > 0 )
//      {
//        if ( fabs(len) < eps )
//        {
//          dx = oh / SQRT2;
//          dy = ov / SQRT2;
//        }
//        else
//        {
//          dx /= len;
//          dy /= len;
//        }
//        circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//      }
//    }
//  }
//}

//void cTileMapCell::projCircle67degB(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType ox, oy, dp;
//      tTileType r;
//      circle.getExt(r, r);
//      ox = circle.getPos().x - sx * r - (pos.x + signx * xw);
//      oy = circle.getPos().y - sy * r - (pos.y - signy * yw);
//      dp = ox * sx + oy * sy;
//      if ( dp < 0 )
//      {
//        tTileType ssx, ssy, lenN, lenP;
//        ssx = sx * -dp;
//        ssy = sy * -dp;
//        lenN = sqrt(ssx*ssx + ssy*ssy);
//        if ( x < y )
//        {
//          lenP = x;
//          y = 0;
//          if ( circle.getPos().x - pos.x < 0 )
//            x *= -1;
//        }
//        else
//        {
//          lenP = y;
//          x = 0;
//          if ( circle.getPos().y - pos.y < 0 )
//            y *= -1;
//        }

//        if ( lenP < lenN )
//          circle.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//        else
//          circle.ReportCollisionVsWorld(ssx, ssy, sx, sy);
//      }
//    }
//    else
//    {
//      if ( signy * ov < 0 )
//        circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//      else
//      {
//        tTileType r;
//        circle.getExt(r, r);
//        tTileType ox, oy;
//        ox = circle.getPos().x - pos.x;
//        oy = circle.getPos().y - (pos.y + signy*yw);
//        if ( signx * ox < 0 )
//          circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//        else
//        {
//          tTileType perp = ox * -sy + oy * sx;
//          if ( perp * signx * signy > 0 )
//          {
//            tTileType len, pen;
//            len = sqrt(ox*ox + oy*oy);
//            pen = r - len;
//            if ( pen > 0 )
//            {
//              ox /= len;
//              oy /= len;
//              circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//            }
//          }
//          else
//          {
//            tTileType dp, pen;
//            dp = ox*sx + oy*sy;
//            pen = r - fabs(dp);
//            if ( pen > 0 )
//              circle.ReportCollisionVsWorld(sx*pen, sy*pen, sx, sy);
//          }
//        }
//      }
//    }
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( signx * oh < 0 )
//        circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//      else
//      {
//        tTileType ox, oy, perp;
//        tTileType r;
//        circle.getExt(r, r);
//        ox = circle.getPos().x - (pos.x + signx*xw);
//        oy = circle.getPos().y - (pos.y - signy*yw);
//        perp = ox * -sy + oy * sx;
//        if ( perp * signx * signy < 0 )
//        {
//          tTileType len, pen;
//          len = sqrt(ox*ox+oy*oy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            ox /= len;
//            oy /= len;
//            circle.ReportCollisionVsWorld(ox*pen, oy*pen, ox, oy);
//          }
//        }
//        else
//        {
//          tTileType dp = ox * sx + oy * sy;
//          tTileType pen = r - fabs(dp);
//          if ( pen > 0 )
//            circle.ReportCollisionVsWorld(sx*pen, sy*pen, sx, sy);
//        }

//      }
//    }
//    else
//    {
//      tTileType r;
//      circle.getExt(r,r);
//      if ( signx * oh + signy * ov > 0 )
//      {
//        tTileType ox, oy, dp;
//        ox = circle.getPos().x - sx*r - (pos.x + signx*xw);
//        oy = circle.getPos().y - sy*r - (pos.y - signy*yw);
//        dp = ox*sx + oy*sy;
//        if ( dp < 0 )
//          circle.ReportCollisionVsWorld(-sx*dp, -sy*dp, sx, sy);
//      }
//      else
//      {
//        tTileType vx, vy, dx, dy, len, pen;
//        vx = pos.x + oh*xw;
//        vy = pos.y + ov*yw;
//        dx = circle.getPos().x - vx;
//        dy = circle.getPos().y - vy;
//        len = sqrt(dx*dx + dy*dy);
//        pen = r - len;
//        if ( pen > 0 )
//        {
//          if ( fabs(len) < eps )
//          {
//            dx = oh / SQRT2;
//            dy = ov / SQRT2;
//          }
//          else
//          {
//            dx /= len;
//            dy /= len;
//          }
//          circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//        }
//      }
//    }
//  }
//}

//void cTileMapCell::projCircleHalf(tTileType x, tTileType y, tTileType oh, tTileType ov, Circle<T> &circle)
//{
//  if ( oh * signx + ov * signy > 0 ) // celldp?
//    return;

//  if ( fabs(oh) < eps )
//  {
//    if ( fabs(ov) < eps )
//    {
//      tTileType r;
//      circle.getExt(r, r);
//      tTileType ox, oy, dp;
//      ox = circle.getPos().x - signx * r - pos.x;
//      oy = circle.getPos().y - signy * r - pos.y;
//      dp = ox*sx + oy*sy;
//      if ( dp < 0 )
//      {
//        tTileType ssx, ssy;
//        ssx = sx*-dp;
//        ssy = sy*-dp;

//        tTileType lenN, lenP;
//        lenN = sqrt(ssx*ssx + ssy*ssy);
//        lenP = sqrt(x*x + y*y);
//        if ( lenP < lenN )
//          circle.ReportCollisionVsWorld(x, y, x/lenP, y/lenP);
//        else
//          circle.ReportCollisionVsWorld(ssx, ssy, signx, signy);
//      }
//    }
//    else
//    {
//      if ( fabs(oh * signx + ov * signy) < eps )
//      {
//        tTileType r;
//        circle.getExt(r, r);
//        tTileType dx, dy;
//        dx = circle.getPos().x - pos.x;
//        if ( dx * signx < 0 )
//          circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//        else
//        {
//          tTileType len, pen;
//          dy = circle.getPos().y - (pos.y + ov * yw);
//          len = sqrt(dx*dx + dy*dy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            if ( fabs(len) < 0 )
//            {
//              dx = signx / SQRT2;
//              dy = ov / SQRT2;
//            }
//            else
//            {
//              dx /= len;
//              dy /= len;
//            }
//            circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//          }
//        }
//      }
//      else
//        circle.ReportCollisionVsWorld(0, y*ov, 0, ov);
//    }
//  }
//  else
//  {
//    if ( fabs(ov) < eps )
//    {
//      if ( fabs(oh * signx + ov * signy) < eps )
//      {
//        tTileType r;
//        circle.getExt(r, r);
//        tTileType dx, dy;
//        dy = circle.getPos().y - pos.y;
//        if ( dy * signy < 0 )
//          circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);
//        else
//        {
//          tTileType len, pen;
//          dx = circle.getPos().x - (pos.x + oh*xw);
//          len = sqrt(dx*dx + dy*dy);
//          pen = r - len;
//          if ( pen > 0 )
//          {
//            if ( fabs(len) < 0 )
//            {
//              dx = signx / SQRT2;
//              dy = ov / SQRT2;
//            }
//            else
//            {
//              dx /= len;
//              dy /= len;
//            }
//            circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//          }
//        }
//      }
//      else
//        circle.ReportCollisionVsWorld(x*oh, 0, oh, 0);

//    }
//    else
//    {
//      tTileType vx, vy, dx, dy, len, pen;
//      tTileType r;
//      circle.getExt(r, r);
//      vx = pos.x + oh * xw;
//      vy = pos.y + ov * yw;
//      dx = circle.getPos().x - vx;
//      dy = circle.getPos().y - vy;
//      len = sqrt(dx*dx+dy*dy);
//      pen = r - len;
//      if ( pen > 0 )
//      {
//        if ( fabs(len) < eps )
//        {
//          dx = oh / SQRT2;
//          dy = ov / SQRT2;
//        }
//        else
//        {
//          dx /= len;
//          dy /= len;
//        }
//        circle.ReportCollisionVsWorld(dx*pen, dy*pen, dx, dy);
//      }
//    }
//  }
//}


tTileType cTileMapCell::minX()
{
  return pos.x - xw;
}

tTileType cTileMapCell::maxX()
{
  return pos.x + xw;
}

tTileType cTileMapCell::minY()
{
  return pos.y - yw;
}

tTileType cTileMapCell::maxY()
{
  return pos.y + yw;
}

void cTileMapCell::SetState(TileEnum::TileID ID)
{
  if ( ID == TileEnum::empty )
  {
    Clear();
    return;
  }

  id = ID;
  UpdateType();
  Draw();
}


// Useless function?
void cTileMapCell::Clear()
{
  id = TileEnum::empty;
  UpdateType();
  Draw();
}

void cTileMapCell::UpdateType()
{
  // Defining sign in x and y
  if ( id == TileEnum::_45degNN || id == TileEnum::concaveNN || id == TileEnum::convexNN || id == TileEnum::_22degNNb ||
       id == TileEnum::_22degNNs || id == TileEnum::_67degNNb || id == TileEnum::_67degNNs )
  {
    signx = signy = -1;
  }
  else if ( id == TileEnum::_45degNP || id == TileEnum::concaveNP || id == TileEnum::convexNP || id == TileEnum::_22degNPb ||
            id == TileEnum::_22degNPs || id == TileEnum::_67degNPb || id == TileEnum::_67degNPs )
  {
    signx = -1;
    signy = 1;
  }
  else if ( id == TileEnum::_45degPN || id == TileEnum::concavePN || id == TileEnum::convexPN || id == TileEnum::_22degPNb ||
            id == TileEnum::_22degPNs || id == TileEnum::_67degPNb || id == TileEnum::_67degPNs )
  {
    signx = 1;
    signy = -1;
  }
  else if ( id == TileEnum::_45degPP || id == TileEnum::concavePP || id == TileEnum::convexPP || id == TileEnum::_22degPPb ||
            id == TileEnum::_22degPPs || id == TileEnum::_67degPPb || id == TileEnum::_67degPPs )
  {
    signx = signy = 1;
  }


  if ( id == TileEnum::full )
  {
    ctype = CTypeEnum::_full;
    signx = signy = sx = sy = 0;
  }
  else if ( id == TileEnum::_45degNN || id == TileEnum::_45degNP || id == TileEnum::_45degPN || id == TileEnum::_45degPP )
  {
    ctype = CTypeEnum::_45deg;
    sx = signx / SQRT2;
    sy = signy / SQRT2;
  }
  else if ( id == TileEnum::concaveNN || id == TileEnum::concaveNP || id == TileEnum::concavePN || id == TileEnum::concavePP )
  {
    ctype = CTypeEnum::concave;
    sx = sy = 0;
  }
  else if ( id == TileEnum::convexNN || id == TileEnum::convexNP || id == TileEnum::convexPN || id == TileEnum::convexPP )
  {
    ctype = CTypeEnum::convex;
    sx = sy = 0;
  }
  else if ( id == TileEnum::_22degNNb || id == TileEnum::_22degNPb || id == TileEnum::_22degPNb || id == TileEnum::_22degPPb )
  {
    ctype = CTypeEnum::_22degb;
    sx = signx / SQRT5;
    sy = signy*2 / SQRT5;
  }
  else if ( id == TileEnum::_22degNNs || id == TileEnum::_22degNPs || id == TileEnum::_22degPNs || id == TileEnum::_22degPPs )
  {
    ctype = CTypeEnum::_22degs;
    sx = signx / SQRT5;
    sy = signy*2 / SQRT5;
  }
  else if ( id == TileEnum::_67degNNb || id == TileEnum::_67degNPb || id == TileEnum::_67degPNb || id == TileEnum::_67degPPb )
  {
    ctype = CTypeEnum::_67degb;
    sx = signx*2 / SQRT5;
    sy = signy / SQRT5;
  }
  else if ( id == TileEnum::_67degNNs || id == TileEnum::_67degNPs || id == TileEnum::_67degPNs || id == TileEnum::_67degPPs )
  {
    ctype = CTypeEnum::_67degs;
    sx = signx*2 / SQRT5;
    sy = signy / SQRT5;
  }
  else if ( id == TileEnum::halfD || id == TileEnum::halfL || id == TileEnum::halfR || id == TileEnum::halfU )
  {
    ctype = CTypeEnum::half;

    if ( id == TileEnum::halfD )
    {
      signx = 0;
      signy = -1;
    }
    else if ( id == TileEnum::halfU )
    {
      signx = 0;
      signy = 1;
    }
    else if ( id == TileEnum::halfL )
    {
      signx = 1;
      signy = 0;
    }
    else if ( id == TileEnum::halfR )
    {
      signx = -1;
      signy = 0;
    }

    sx = signx;
    sy = signy;
  }
  else if ( id == TileEnum::empty )
  {
    ctype = CTypeEnum::_empty;
    signx = signy = sx = sy = 0;
  }
  else
  {
    // TODO: Wrong id. Show error message.
    // Trace Bad Tile.
  }
}

void cTileMapCell::Draw()
{
  //    s.pos.x = (float)(pos.x-xw);
  //    s.pos.y = (float)(pos.y-yw);
  //
  //    if ( ctype == CTypeEnum::_full )
  //        s.beginAnimation(0);
  //    if ( ctype == CTypeEnum::_45deg )
  //        s.beginAnimation(1);
  //    if ( ctype == CTypeEnum::concave )
  //        s.beginAnimation(2);
  //    if ( ctype == CTypeEnum::convex )
  //        s.beginAnimation(3);
  //    if ( ctype == CTypeEnum::_22degs )
  //        s.beginAnimation(4);
  //    if ( ctype == CTypeEnum::_22degb )
  //        s.beginAnimation(5);
  //    if ( ctype == CTypeEnum::_67degs )
  //        s.beginAnimation(6);
  //    if ( ctype == CTypeEnum::_67degb )
  //        s.beginAnimation(7);
  //    if ( ctype == CTypeEnum::half )
  //        s.beginAnimation(8);
  //    // GotoAndStop(id+1) ?
  //    s.render();
}


