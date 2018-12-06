# Surface Bin Format {#SurfaceBinFormat}


2 Byte Integer : **Landing Point Longitude**

[0, 359]
___

2 Byte Integer : **Landing Point Latitude**

[1, 119], equator is at 60.
___

4 Byte Integer : **Quadrant Capsule X Position**

[0, 3276800], aligned to boundaries of 16384.
___

4 Byte Integer : **Quadrant Capsule Z Position**

[0, 3276800], aligned to boundaries of 16384.
___

4 Byte Integer : **Sub-Quadrant Capsule X Position**

[0, 16384]
___

4 Byte Integer : **Sub-Quadrant Capsule Z Position**

[0, 16384]
___

4 Byte Float : **Player X Position**

[0, 3276800]
___

4 Byte Float : **Player Y Position**

[-260000, 0], zero is sea level.
___

4 Byte Float : **Player Z Position**

[0, 3276800]
___

4 Byte Float : **Camera Alpha Angle**

[-45, 45], represents yaw in degrees.
___

4 Byte Float : **Camera Beta Angle**

[-180, 180], represents pitch in degrees.
___

2 Byte Integer : **Radiation Visor Animation Delta**

[-5, 5]
___

2 Byte Integer : **Radiation Visor Animation Count**

[0, 170]
___

1 Byte : **Radiation Visor Flag**

0 = Opened
1 = Closed
___

45 Bytes : **Total Size**
