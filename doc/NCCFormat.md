# NCC File Format {#NCCFormat}

2 Byte Integer : **Polygon Count**

N = Number of Polygons in the File
___

N Bytes : **Vertex Count**

3 = Triangle
4 = Quad
___

16 * N Bytes : **X Coordinates**

Given in 4 byte floats, with the fourth byte left empty if it's a triangle.
___

16 * N Bytes : **Y Coordinates**
___

16 * N Bytes : **Z Coordinates**
___

N Bytes : **Color Intensity**

[1, 62] = Color Intensity of Each Polygon
___

2 + 50 * N Bytes : **Total File Size**
