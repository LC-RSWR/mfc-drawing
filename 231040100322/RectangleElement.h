#pragma once
#include "Element.h"
#include "LineElement.h"


// RectangleElement �ࣺ�̳��� Element����ʾһ������
class RectangleElement : public Element {
public:
    CPoint topLeft, bottomRight;  // ���ϽǺ����½ǵĵ�
    
    // ���캯�������������㹹�����
    RectangleElement(CPoint point1, CPoint point2, COLORREF color = RGB(0, 0, 0))
        : Element(point1, point2, color) {

        // �������ϽǺ����½ǵĵ�
      
        int minX = (point1.x < point2.x) ? point1.x : point2.x;  // ѡ���С�� x
        int minY = (point1.y < point2.y) ? point1.y : point2.y;  // ѡ���С�� y
        int maxX = (point1.x > point2.x) ? point1.x : point2.x;  // ѡ��ϴ�� x
        int maxY = (point1.y > point2.y) ? point1.y : point2.y;  // ѡ��ϴ�� y

        // ���� CPoint ����
        topLeft = CPoint(minX, minY);      // ���Ͻǵ�
        bottomRight = CPoint(maxX, maxY);  // ���½ǵ�


        point1 = topLeft;
        point2 = bottomRight;
    }

    void fill(CDC* pDC) {}  // ���麯������������Ҫʵ��

    // ��ȡ���ε��ĸ�����
    std::vector<CPoint> getVertices() const {
        std::vector<CPoint> vertices;
        vertices.push_back(topLeft); // ���Ͻ�
        vertices.push_back(CPoint(bottomRight.x, topLeft.y)); // ���Ͻ�
        vertices.push_back(bottomRight); // ���½�
        vertices.push_back(CPoint(topLeft.x, bottomRight.y)); // ���½�
        return vertices;
    }

    // ���ƾ��εķ�����ʹ�������߱�ʾ���Σ�
    void draw(CDC* pDC) override {
        // ��ȡ���ε��ĸ�����
        std::vector<CPoint> vertices = getVertices();

        // ʹ�� Bresenham ֱ���㷨����������
        LineElement topEdge(vertices[0], vertices[1], color);  // �ϱ�
        LineElement rightEdge(vertices[1], vertices[2], color); // �ұ�
        LineElement bottomEdge(vertices[2], vertices[3], color); // �±�
        LineElement leftEdge(vertices[3], vertices[0], color);  // ���

        // ���ƾ����ĸ���
        topEdge.draw(pDC);
        rightEdge.draw(pDC);
        bottomEdge.draw(pDC);
        leftEdge.draw(pDC);
    }

    // ƽ�ƺ���
    void translate(int dx, int dy) {

        topLeft.Offset(dx, dy);
        bottomRight.Offset(dx, dy);

        point1 = topLeft;
        point2 = bottomRight;
    }

    // ���ź���
    void scale(double scaleX, double scaleY, CPoint origin) {


        // ���Ź�ʽ:
        // x' = (x - origin.x) * scaleX + origin.x
        // y' = (y - origin.y) * scaleY + origin.y

        int mid_x = (topLeft.x + bottomRight.x) / 2;
        int mid_y = (topLeft.y + bottomRight.y) / 2;
        CPoint mid(mid_x, mid_y);
        origin = mid;

        int x1_new = (point1.x - origin.x) * scaleX + origin.x;
        int y1_new = (point1.y - origin.y) * scaleY + origin.y;
        topLeft = CPoint(x1_new, y1_new);

        int x2_new = (point2.x - origin.x) * scaleX + origin.x;
        int y2_new = (point2.y - origin.y) * scaleY + origin.y;
        bottomRight = CPoint(x2_new, y2_new);
    }

    // ��ת����
    void rotate(double angle, CPoint origin) {
        // ��ת����:
        // x' = cos(angle) * (x - origin.x) - sin(angle) * (y - origin.y) + origin.x
        // y' = sin(angle) * (x - origin.x) + cos(angle) * (y - origin.y) + origin.y

        int mid_x = (topLeft.x + bottomRight.x) / 2;
        int mid_y = (topLeft.y + bottomRight.y) / 2;
        CPoint mid(mid_x, mid_y);
        origin = mid;

        // ��point1������ת
        double radian = angle;  // ���贫��ĽǶ��ǻ�����
        double cosAngle = cos(radian);
        double sinAngle = sin(radian);

        int x1_new = cosAngle * (topLeft.x - origin.x) - sinAngle * (topLeft.y - origin.y) + origin.x;
        int y1_new = sinAngle * (topLeft.x - origin.x) + cosAngle * (topLeft.y - origin.y) + origin.y;
        topLeft = CPoint(x1_new, y1_new);

        // ��point2������ת
        int x2_new = cosAngle * (bottomRight.x - origin.x) - sinAngle * (bottomRight.y - origin.y) + origin.x;
        int y2_new = sinAngle * (bottomRight.x - origin.x) + cosAngle * (bottomRight.y - origin.y) + origin.y;
        bottomRight = CPoint(x2_new, y2_new);
    }


};
