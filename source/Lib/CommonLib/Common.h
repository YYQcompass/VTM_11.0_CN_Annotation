/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2020, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     Common.h
 *  \brief    Common 2D-geometrical structures
 */

#ifndef __COMMON__
#define __COMMON__

#include "CommonDef.h"

typedef int PosType;
typedef uint32_t SizeType;
#if CN_ANNOTATION
// Position 结构体
#endif
struct Position
{
#if CN_ANNOTATION
  // 成员变量x和y分别表示横纵坐标值
#endif
  PosType x;
  PosType y;
#if CN_ANNOTATION
  // 默认构造函数，将坐标设为原点（0, 0）
#endif
  Position()                                   : x(0),  y(0)  { }
#if CN_ANNOTATION
  // 带参数构造函数，根据输入的坐标值构建Position对象
#endif
  Position(const PosType _x, const PosType _y) : x(_x), y(_y) { } 
#if CN_ANNOTATION
  // 重载!=运算符，判断两个 Position 对象是否不相等
#endif
  bool operator!=(const Position &other)  const { return x != other.x || y != other.y; }
#if CN_ANNOTATION
  // 重载==运算符，判断两个 Position 对象是否相等
#endif
  bool operator==(const Position &other)  const { return x == other.x && y == other.y; }
#if CN_ANNOTATION
  // 计算当前 Position 与输入 Position 相加后的新的 Position
#endif
  Position offset(const Position pos)                 const { return Position(x + pos.x, y + pos.y); }
  Position offset(const PosType _x, const PosType _y) const { return Position(x + _x   , y + _y   ); }
#if CN_ANNOTATION
  // 将当前 Position 重新定位到新的坐标位置
#endif
  void     repositionTo(const Position newPos)              { x  = newPos.x; y  = newPos.y; }
#if CN_ANNOTATION
  // 将当前Position转换为相对于某一原点的相对位置
#endif
  void     relativeTo  (const Position origin)              { x -= origin.x; y -= origin.y; }
#if CN_ANNOTATION
  // 重载-运算符，计算当前Position与输入Position之间的差值
#endif
  Position operator-( const Position &other )         const { return{ x - other.x, y - other.y }; }
#if CN_ANNOTATION
  //
   // 关于上面两个const的进一步说明：
   // 函数参数前的 const：表示传入的 Position 对象 other 是常量引用，意味着在该成员函数内部不会修改 other 的内容。
   // 函数声明末尾的 const： 表示该成员函数是一个常量成员函数。当一个成员函数被声明为 const，这意味着它不会改变调用它的对象的状态。
   //    对于这个 - 运算符重载函数而言，尽管它返回一个新的 Position 对象，但它并没有改变调用该函数的对象的 x 和 y 值。
   //
#endif
};
#if CN_ANNOTATION
// 定义 Size 结构体，用于表示一个矩形区域的尺寸（宽和高）
#endif
struct Size
{
#if CN_ANNOTATION
  // 成员变量width和height分别表示矩形区域的宽度和高度
#endif
  SizeType width;
  SizeType height;
#if CN_ANNOTATION
  // 默认构造函数，将尺寸设为零（0, 0）
#endif
  Size()                                              : width(0),      height(0)       { }
#if CN_ANNOTATION
  // 带参数构造函数，根据输入的宽度和高度构建Size对象
#endif
  Size(const SizeType _width, const SizeType _height) : width(_width), height(_height) { }

  bool operator!=(const Size &other)      const { return (width != other.width) || (height != other.height); }
  bool operator==(const Size &other)      const { return (width == other.width) && (height == other.height); }
#if CN_ANNOTATION
  // 计算Size对象所表示矩形区域的面积
#endif
  uint32_t area()                             const { return (uint32_t) width * (uint32_t) height; }
#if REUSE_CU_RESULTS_WITH_MULTIPLE_TUS
#if CN_ANNOTATION
  // 根据输入的新尺寸调整当前Size对象的尺寸
#endif
  void resizeTo(const Size newSize)             { width = newSize.width; height = newSize.height; }
#endif
};
#if CN_ANNOTATION
// 定义了一个名为 Area 的结构体，它继承自Position和Size结构体，从而结合了位置和尺寸信息来表示一个矩形区域。
#endif
struct Area : public Position, public Size
{
  Area()                                                                         : Position(),       Size()       { }
  Area(const Position &_pos, const Size &_size)                                  : Position(_pos),   Size(_size)  { }
  Area(const PosType _x, const PosType _y, const SizeType _w, const SizeType _h) : Position(_x, _y), Size(_w, _h) { }
#if CN_ANNOTATION
  // 提供对 Area 作为 Position 和 Size 的访问接口
#endif
        Position& pos()                           { return *this; }
  const Position& pos()                     const { return *this; }
        Size&     size()                          { return *this; }
  const Size&     size()                    const { return *this; }
#if CN_ANNOTATION
  // 获取矩形区域的四个顶点与中心点
#endif
  const Position& topLeft()                 const { return *this; }
        Position  topRight()                const { return { (PosType) (x + width - 1), y                          }; }
        Position  bottomLeft()              const { return { x                        , (PosType) (y + height - 1) }; }
        Position  bottomRight()             const { return { (PosType) (x + width - 1), (PosType) (y + height - 1) }; }
        Position  center()                  const { return { (PosType) (x + width / 2), (PosType) (y + height / 2) }; }
#if CN_ANNOTATION
  // 判断给定点是否在区域内
#endif
  bool contains(const Position &_pos)       const { return (_pos.x >= x) && (_pos.x < (x + width)) && (_pos.y >= y) && (_pos.y < (y + height)); }
#if CN_ANNOTATION
  // 判断给定区域是否完全在本区域内，其实就是判断左上点和右下点是否都在区域内
#endif
  bool contains(const Area &_area)          const { return contains(_area.pos()) && contains(_area.bottomRight()); }

  bool operator!=(const Area &other)        const { return (Size::operator!=(other)) || (Position::operator!=(other)); }
  bool operator==(const Area &other)        const { return (Size::operator==(other)) && (Position::operator==(other)); }
};

struct UnitScale
{
  UnitScale()                 : posx( 0), posy( 0), area(posx+posy) {}
  UnitScale( int sx, int sy ) : posx(sx), posy(sy), area(posx+posy) {}
  int posx;
  int posy;
  int area;

  template<typename T> T scaleHor ( const T &in ) const { return in >> posx; }
  template<typename T> T scaleVer ( const T &in ) const { return in >> posy; }
  template<typename T> T scaleArea( const T &in ) const { return in >> area; }

  Position scale( const Position &pos  ) const { return { pos.x >> posx, pos.y >> posy }; }
  Size     scale( const Size     &size ) const { return { size.width >> posx, size.height >> posy }; }
  Area     scale( const Area    &_area ) const { return Area( scale( _area.pos() ), scale( _area.size() ) ); }
};
namespace std
{
  template <>
  struct hash<Position> 
  {
    uint64_t operator()(const Position& value) const
    {
      return (((uint64_t)value.x << 32) + value.y);
    }
  };

  template <>
  struct hash<Size> 
  {
    uint64_t operator()(const Size& value) const
    {
      return (((uint64_t)value.width << 32) + value.height);
    }
  };
}
inline size_t rsAddr(const Position &pos, const uint32_t stride, const UnitScale &unitScale )
{
  return (size_t)(stride >> unitScale.posx) * (size_t)(pos.y >> unitScale.posy) + (size_t)(pos.x >> unitScale.posx);
}

inline size_t rsAddr(const Position &pos, const Position &origin, const uint32_t stride, const UnitScale &unitScale )
{
  return (stride >> unitScale.posx) * ((pos.y - origin.y) >> unitScale.posy) + ((pos.x - origin.x) >> unitScale.posx);
}

inline size_t rsAddr(const Position &pos, const uint32_t stride )
{
  return stride * (size_t)pos.y + (size_t)pos.x;
}

inline size_t rsAddr(const Position &pos, const Position &origin, const uint32_t stride )
{
  return stride * (pos.y - origin.y) + (pos.x - origin.x);
}

inline Area clipArea(const Area &_area, const Area &boundingBox)
{
  Area area = _area;

  if (area.x + area.width > boundingBox.x + boundingBox.width)
  {
    area.width = boundingBox.x + boundingBox.width - area.x;
  }

  if (area.y + area.height > boundingBox.y + boundingBox.height)
  {
    area.height = boundingBox.y + boundingBox.height - area.y;
  }

  return area;
}


class SizeIndexInfo
{
public:
  SizeIndexInfo(){}
  virtual ~SizeIndexInfo(){}
  SizeType numAllWidths()               { return (SizeType)m_idxToSizeTab.size(); }
  SizeType numAllHeights()              { return (SizeType)m_idxToSizeTab.size(); }
  SizeType numWidths()                  { return (SizeType)m_numBlkSizes; }
  SizeType numHeights()                 { return (SizeType)m_numBlkSizes; }
  SizeType sizeFrom( SizeType idx )     { return m_idxToSizeTab[idx]; }
  SizeType idxFrom( SizeType size )     { CHECKD( m_sizeToIdxTab[size] == std::numeric_limits<SizeType>::max(), "Index of given size does NOT EXIST!" ); return m_sizeToIdxTab[size]; }
  bool     isCuSize( SizeType size )    { return m_isCuSize[size]; }
  virtual void init( SizeType maxSize ) {}

protected:

  void xInit()
  {
    m_isCuSize.resize( m_sizeToIdxTab.size(), false );

    std::vector<SizeType> grpSizes;

    for( int i = 0, n = 0; i < m_sizeToIdxTab.size(); i++ )
    {
      if( m_sizeToIdxTab[i] != std::numeric_limits<SizeType>::max() )
      {
        m_sizeToIdxTab[i] = n;
        m_idxToSizeTab.push_back( i );
        n++;
      }

      if( m_sizeToIdxTab[i] != std::numeric_limits<SizeType>::max() && m_sizeToIdxTab[i >> 1] != std::numeric_limits<SizeType>::max() && i >= 4 )
      {
        m_isCuSize[i] = true;
      }

      // collect group sizes (for coefficient group coding)
      SizeType grpSize = i >> ( ( i & 3 ) != 0 ? 1 : 2 );
      if( m_sizeToIdxTab[i] != std::numeric_limits<SizeType>::max() && m_sizeToIdxTab[grpSize] == std::numeric_limits<SizeType>::max() )
      {
        grpSizes.push_back( grpSize );
      }
    }

    m_numBlkSizes = (SizeType)m_idxToSizeTab.size();

    for( SizeType grpSize : grpSizes )
    {
      if( grpSize > 0 && m_sizeToIdxTab[grpSize] == std::numeric_limits<SizeType>::max() )
      {
        m_sizeToIdxTab[grpSize] = (SizeType)m_idxToSizeTab.size();
        m_idxToSizeTab.push_back( grpSize );
      }
    }
  };

  std::vector<bool    > m_isCuSize;
  int                   m_numBlkSizes; // as opposed to number all sizes, which also contains grouped sizes
  std::vector<SizeType> m_sizeToIdxTab;
  std::vector<SizeType> m_idxToSizeTab;
};

class SizeIndexInfoLog2 : public SizeIndexInfo
{
public:
  SizeIndexInfoLog2(){}
  ~SizeIndexInfoLog2(){};

  void init( SizeType maxSize )
  {
    for( int i = 0, n = 0; i <= maxSize; i++ )
    {
      SizeType val = std::numeric_limits<SizeType>::max();
      if( i == ( 1 << n ) )
      {
        n++;
        val = i;
      }
      m_sizeToIdxTab.push_back( val );
    }
    SizeIndexInfo::xInit();
  }
};
#endif
