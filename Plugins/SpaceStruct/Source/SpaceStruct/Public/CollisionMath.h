#pragma once
#include <vector>


// //  SAT
/// SAT 只适用于凸多边形，你的代码没有验证输入。
// struct Vec2
// {
// 	float x , y;
//
// 	Vec2 operator- (const Vec2& b) const
// 	{
// 		return Vec2{ x- b.x , y- b.y };
// 	}
// 	Vec2 operator* (float scalar) const{ return {x * scalar , y * scalar}; }
// 	
// 	float dot(const Vec2 & b) const
// 	{
// 		return x * b.x + y * b.y;
// 	}
// 	// 获取法线
// 	Vec2 getNormal() const {return {-y ,x};}
// 	// 归一化 
// 	Vec2 normalized()const
// 	{
// 		float len = length();
// 		return (len > 0) ? Vec2{x / len, y / len} : Vec2{0, 0};
// 	}
// 	float length() const
// 	{
// 		return std::sqrt(x*x + y*y);
// 	}
// 	
// };
//
// struct CollisionInfo
// {
// 	bool intersected =false;
// 	Vec2 mtvAxis{0 , 0}; // 最小 穿透方向
// 	float depth = 9999999.0f ;  // 最小 穿透深度
// };
//
// typedef std::vector<Vec2> Polygon; // 多边形
//
// // 将多边形每一个顶点 到 投影到 一个轴   
// void projectPolygon(const Polygon & poly , Vec2 axis , float & min , float & max)
// {
// 	// 归一化 轴
// 	float len = axis.length();
// 	axis.x  /= len;
// 	axis.y  /= len;
// 	
// 	//  每一个边都做投影
// 	min = max = poly[0].dot(axis);
// 	for (const Vec2 & v : poly)
// 	{
// 		float temp = v.dot(axis);
// 		min = std::min(min , temp);
// 		max = std::max(max, temp);
// 	}
// }
// // SAT 检测  包含 最小 穿透方向 以及 距离
// CollisionInfo checkSAT(const std::vector<Vec2>& polyA, const std::vector<Vec2>& polyB) {
// 	CollisionInfo info;
// 	info.intersected = true;
//
// 	auto getAxes = [](const std::vector<Vec2>& p) {
// 		std::vector<Vec2> axes;
// 		for (size_t i = 0; i < p.size(); ++i) {
// 			Vec2 edge = p[(i + 1) % p.size()] - p[i];
// 			axes.emplace_back(edge.getNormal()); // 法向量
// 		}
// 		return axes;
// 	};
//
// 	std::vector<Vec2> allAxes = getAxes(polyA);
// 	std::vector<Vec2> axesB = getAxes(polyB);
// 	allAxes.insert(allAxes.end(), axesB.begin(), axesB.end());
//
// 	for (Vec2& axis : allAxes) {
// 		axis = axis.normalized(); // MTV 必须使用归一化轴
// 		float minA, maxA, minB, maxB;
// 		projectPolygon(polyA, axis, minA, maxA);
// 		projectPolygon(polyB, axis, minB, maxB);
//
// 		// 检查重叠
// 		float overlap = std::min(maxA, maxB) - std::max(minA, minB); //
// 		if (overlap <= 0) {
// 			info.intersected = false;
// 			return info; // 发现缝隙，立即退出
// 		}
//
// 		// 寻找最小重叠量
// 		if (overlap < info.depth) {
// 			info.depth = overlap;
// 			info.mtvAxis = axis;
// 		}
// 	}
//
// 	// 修正方向：确保 MTV 指向从 A 到 B 的方向（方便后续物理位移）
// 	// 简单做法：检查 B 中心 - A 中心 在 mtvAxis 上的投影
// 	return info;
// }





//
// GJK

//
// GJK 算法完整流程总结
// 一、核心思想
// 通过判断两个凸多边形的闵可夫斯基差是否包含原点来确定是否相交。
//
// 相交 ⇔ 原点 ∈ (A ⊕ -B)
//
// 用迭代的方式逐步构建一个包围原点的单纯形
//
// 二、主流程
// 第一步：初始化
// 设置初始搜索方向 d（通常取 (1, 0)）
//
// 清空单纯形（用于存储支撑点的容器）
//
// 第二步：获取第一个支撑点
// 计算闵可夫斯基差支撑点：support(A, d) - support(B, -d)
//
// 将该点加入单纯形
//
// 第三步：设置搜索方向
// 将搜索方向 d 指向原点：d = -第一个支撑点
//
// 第四步：进入迭代循环
// 4.1 获取新支撑点
// 沿当前方向 d 获取新的闵可夫斯基差支撑点
//
// 4.2 终止条件检查
// 如果新支撑点在 d 上的投影 < 0
//
// 说明未能越过原点 → 返回"不相交"
//
// 4.3 将新点加入单纯形
// 4.4 处理单纯形
// 根据单纯形中点的数量进行不同处理：
//
// 情况一：线段（2个点）
//
// 计算新搜索方向：垂直于线段且指向原点
//
// 保持单纯形为2个点
//
// 继续循环
//
// 情况二：三角形（3个点）
//
// 判断原点相对于三条边的位置
//
// 如果原点在某条边的外侧：
//
// 删除对面的顶点
//
// 更新搜索方向为该边的垂线方向
//
// 继续循环
//
// 如果原点在三角形内部：
//
// 返回"相交"
//
// 三、关键函数说明
// 支撑函数
// 作用：在给定方向上找到多边形最远的点
//
// 原理：计算所有顶点与方向向量的点积，取最大值对应的点
//
// 闵可夫斯基差支撑函数
// 公式：support(A, d) - support(B, -d)
//
// 意义：得到闵可夫斯基差形状在方向 d 上的最远点
//
// 三重叉积（用于计算垂线方向）
// 公式：(a × b) × c = b(a·c) - a(b·c)
//
// 用途：计算线段的垂直方向，且保证指向原点一侧





//
// struct Vec2
// {
// 	float x ,y;
// 	Vec2 operator-() const{return {-x , -y};}
// 	Vec2 operator-(const Vec2& b) const{
// 		return {x-b.x , y - b.y};
// 	}
// 	float dot(const Vec2 & v) const{
// 		return x * v.x  + y * v.y;
// 		// x1 *x2 + y1 * y2;
// 	}
// 	Vec2 cross(float s) const { return {s * y , -s * x};}
// 	float length() const{
// 		return std::sqrt(x*x + y*y);
// 	}
// 	Vec2 normalized()
// 	{
// 		float len = length();
// 		return (len > 0) ? Vec2{x / len, y / len} : Vec2{0, 0};
// 	}
// 	
// };
//
// struct CollisionInfo
// {
// 	bool intersected =false;
// 	Vec2 mtvAxis{0 , 0}; // 最小 穿透方向
// 	float depth = 9999999.0f ;  // 最小 穿透深度
// };
//
//
//
// struct Edge
// {
// 	Vec2 normal;    // 法线
// 	float distance; // 到达 原点的距离
// 	size_t index;   // 指向多边形 顶点的索引
// };
// // Support 函数
// // 1. 支撑函数：在方向 d 上找到形状最远的点
// Vec2 getSupport(const std::vector<Vec2>& poly, Vec2 d) {
// 	float MaxDot = poly[0].dot(d);
// 	int index = 0;
// 	for (int  i = 1; i < poly.size(); i++)
// 	{
// 		float Dot = poly[i].dot(d);
// 		if (Dot > MaxDot)
// 		{
// 			MaxDot = Dot;
// 			index = i;
// 		}
// 	}
// 	return poly[index];
// }
//
//
// // 闵可夫斯基差的支撑点
// Vec2 minkowskiSupport(const std::vector<Vec2>& polyA , const std::vector<Vec2>&polyB , Vec2 d)
// {
// 	return getSupport(polyA , d) - getSupport(polyB , -d);
// }
//
// // 辅助函数：三向量叉乘简化版 (仅限 2D 逻辑使用)
// // 实际上在 2D 中，我们常用垂直向量来模拟
// Vec2 tripleProduct(const Vec2& a, const Vec2& b, const Vec2& c) {
// 	// (A x B) x C = B(A·C) - A(B·C) 三重叉积 公式
// 	float ac = a.dot(c);
// 	float bc = b.dot(c);
// 	return { b.x * ac - a.x * bc, b.y * ac - a.y * bc };
// }
// // 处理单纯形
// /**
//  * @param simplex 当前已经有的 单纯形点 可能是 2个  或者  是 3个
//  * @param d 
//  * @return 
//  */
// bool handleSimplex(std::vector<Vec2>& simplex , Vec2 & d)
// {
// 	if (simplex.size() == 2) // 线段
// 	{
// 		Vec2 B = simplex[0];
// 		Vec2 A= simplex[1];
// 		Vec2 AB = B -A;
// 		Vec2 AO = -A; 
// 		// 方向d 为  AB 的 法线 ， 且指向原定
// 		d = tripleProduct(AB , AO , AB);
// 		return false;
// 	}
// 	else if (simplex.size() == 3) {
// 		// 【三角形情况】
// 		Vec2 A = simplex[2]; // 最近加入的点
// 		Vec2 B = simplex[1];
// 		Vec2 C = simplex[0];
// 		Vec2 AB = B - A;
// 		Vec2 AC = C - A;
// 		Vec2 AO = -A;
//
// 		// 计算 AB 和 AC 的法线（向外指）
// 		Vec2 ABperp = tripleProduct(AC, AB, AB);
// 		Vec2 ACperp = tripleProduct(AB, AC, AC);
//
// 		// 检查原点是否在 AB 外侧
// 		if (ABperp.dot(AO) > 0) {
// 			simplex.erase(simplex.begin()); // 扔掉 C
// 			d = ABperp;
// 			return false;
// 		}
// 		// 检查原点是否在 AC 外侧
// 		if (ACperp.dot(AO) > 0) {
// 			simplex.erase(simplex.begin() + 1); // 扔掉 B
// 			d = ACperp;
// 			return false;
// 		}
//
// 		// 原点既不在 AB 外，也不在 AC 外，说明在三角形内！
// 		return true;
// 	}
// 	return false;
// }
//
//
//
//
// // 寻找多边形中离原点最近的边
// Edge findClosestEdge(const std::vector<Vec2>& polytope) {
// 	Edge closest;
// 	closest.distance = FLT_MAX;
//
// 	for (size_t i = 0; i < polytope.size(); i++) {
// 		Vec2 a = polytope[i];
// 		Vec2 b = polytope[(i + 1) % polytope.size()];
//         
// 		Vec2 ab = b - a;
// 		// 计算向外的法线 (2D 中根据顶点顺序确定)
// 		Vec2 n = {ab.y, -ab.x}; 
// 		n = n.normalized();
//         
// 		float d = n.dot(a); // 原点到直线的投影距离
// 		if (d < 0) { // 如果距离为负，说明法线指反了
// 			d = -d;
// 			n = -n;
// 		}
// 		if (d < closest.distance) {
// 			closest.distance = d;
// 			closest.normal = n;
// 			closest.index = (i + 1) % polytope.size();
// 		}
// 	}
// 	return closest;
// }
//
// bool GJK(const std::vector<Vec2>& polyA, const std::vector<Vec2>& polyB)
// {
// 	Vec2 d= {1 , 0}; // 初始方向
// 	std::vector<Vec2> simplex;
// 	
// 	simplex.push_back(minkowskiSupport(polyA,  polyB, d)); //  初始的 一个 单纯形 点
// 	d = -simplex[0]; // 向 原点寻找
// 	while (true)
// 	{
// 		Vec2 A = minkowskiSupport(polyA,  polyB, d); // 
// 		if (A.dot(d) < 0) return false; // 我们找到的  新的 支撑点 甚至 没有再 d 方向上 越过 原点 所以 不用计算了
// 		simplex.push_back(A);
// 		if (handleSimplex(simplex,d)) return true;
// 	}
// 	
// }
//
// CollisionInfo epa(const std::vector<Vec2>& polyA, const std::vector<Vec2>& polyB, std::vector<Vec2> simplex) {
// 	// simplex 是 GJK 结束后包含原点的三角形
// 	std::vector<Vec2> polytope = simplex; 
//		
// 	while (true) {
// 		// 1. 找到当前离原点最近的边
// 		Edge edge = findClosestEdge(polytope);
//		
// 		// 2. 沿着这条边的法线找新的支撑点
// 		Vec2 p = minkowskiSupport(polyA, polyB, edge.normal);
//		
// 		// 3. 检查是否还能继续扩张
// 		float d = p.dot(edge.normal);
// 		if (std::abs(d - edge.distance) < 0.001f) {
// 			// 无法再向外扩张了，当前边就是边缘
// 			CollisionInfo info;
// 			info.intersected = true;
// 			info.depth = d;
// 			info.mtvAxis = edge.normal;
// 			return info;
// 		}
//			
// 		// 4. 扩张：在对应位置插入新点
// 		polytope.insert(polytope.begin() + edge.index, p);
// 	}	
// }	


//
// EPA 算法完整流程总结
// 一、核心思想
// EPA 用于计算穿透深度和方向，作为 GJK 的补充。
//
// 输入：GJK 得到的包含原点的单纯形（三角形）
//
// 输出：最小穿透向量（MTV）= 穿透深度 + 方向
//
// 原理：不断扩张多面体，找到离原点最近的边
// 二、主流程
// 第一步：初始化
// 将 GJK 得到的单纯形作为初始多面体
//
// 这个单纯形已经包含原点
//
// 第二步：进入迭代循环
// 2.1 寻找最近边
// 遍历多面体的所有边
//
// 计算每条边到原点的距离
//
// 记录距离最小的边（最近边）
//
// 同时记录该边的法线方向
//
// 2.2 沿法线方向获取新支撑点
// 以最近边的法线作为搜索方向
//
// 计算闵可夫斯基差在该方向上的新支撑点
//
// 2.3 收敛判断
// 计算新支撑点在法线上的投影距离
//
// 如果该距离与当前最近边的距离非常接近（差值小于阈值）
//
// 说明无法再向外扩张
//
// 当前边就是闵可夫斯基差上离原点最近的边
//
// 结束循环
//
// 2.4 扩张多面体
// 将新支撑点插入到最近边的位置
//
// 具体插入位置：在边的两个端点之间
//
// 继续循环


class CollisionMath
{
public:
	
};
