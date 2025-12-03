/**
 * Author: jiangly
 * Date: 2025-03-12
 * Source: https://cp-algorithms.com/geometry/halfplane-intersection.html
 * Description: inputs set of (infinite) lines (vectors must cycle around the shape in ccw), 
 * returns the bounded convex polygon('s vertices) that was formed by them. 
 * If unbounded: empty vec; if no kernel exists: empty vec.
 * Time: O(N\log N)
 */
#pragma once

#include "Point.h"

template<class T>
struct Line {
    Point<T> a; Point<T> b;
    Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
int sgn(Point<T> a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;}
template<class T>
T dot(Point<T> a, Point<T> b) {return a.x * b.x + a.y * b.y;}
template<class T>
T cross(Point<T> a, Point<T> b) {return a.x * b.y - a.y * b.x;}
template<class T>
bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) > 0;}

// any fxn that uses this must be Point<double> to avoid int div.
template<class T>
Point<T> lineIntersection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T>
std::vector<Point<T>> halfPlane(std::vector<Line<T>> lines) {
    sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a; auto d2 = l2.b - l2.a;
        if (sgn(d1) != sgn(d2)) {return sgn(d1) == 1;}
        return cross(d1, d2) > 0;
    });
    deque<Line<T>> ls; deque<Point<T>> ps;
    for (auto l : lines) {
        if (ls.empty()) {ls.push_back(l);continue;}
        while (!ps.empty() && !pointOnLineLeft(ps.back(), l)) {
            ps.pop_back();ls.pop_back();}
        while (!ps.empty() && !pointOnLineLeft(ps[0], l)) {
            ps.pop_front();ls.pop_front();}
        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);ls[0] = l;}
                continue;}
            return {};
        }
        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }
    while (!ps.empty() && !pointOnLineLeft(ps.back(), ls[0])) {
        ps.pop_back();ls.pop_back();}
    if (ls.size() <= 2) {return {};}
    ps.push_back(lineIntersection(ls[0], ls.back()));
    return vector<Point<T>>(ps.begin(), ps.end());
}
