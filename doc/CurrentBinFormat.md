# Current Bin Format {#CurrentBinFormat}

1 Byte Integer : **Orbit Synchronization Mode Flag**

0 = Tracking Disabled

1 = Fixed-Point Chase

2 = Far Chase

3 = Synchrone Orbit

4 = High-Speed Orbit

5 = Near Chase
___

1 Byte Integer : **Radiation Protection Flag**

1 = Don't Allow Close Proximity to Star
___ 

1 Byte Integer : **Planet Finder Flag**

1 = Show Number of Bodies in Nearest Star System
___ 

1 Byte Integer : **Starfield Amplificator Flag**

0 = Inactive

1 = Active
___ 

1 Byte Integer : **Internal Light Power**

[0, 63] = Power of Internal Light
___ 

1 Byte Integer : **Internal Light Power Variation**

-1 = Light is On

+1 = Light is Off
___ 

1 Byte Integer : **Lithium Quantity**

[0, 120] = Quantity of Lithium in Stardrifter
___ 

1 Byte Integer : **Reverse Pitch Control Flag**

0 = Normal

1 = Reversed
___ 

1 Byte Integer : **AP Targeting Flag**

1 = Currently Selecting Remote Target
___ 

1 Byte Integer : **AP Targeted Flag**

-1 = Remote Target is a Set of Coordinates

0 = No Target Selected

1 = Remote Target is a Star
___ 

1 Byte Integer : **IP Targeting Flag**

1 = Currently Selecting Local Target
___ 

1 Byte Integer : **IP Targeted**

-1 = No Target

[0, 79] = Planet Number
___ 

1 Byte Integer : **IP Reaching Flag**

1 = Ship on Fine Approach
___ 

1 Byte Integer : **IP Reached Flag**

1 = Ship Arrived at Local Target
___ 

1 Byte Integer : **AP Target Spin**

[?, ?] = Rotation Speed of Target Star
___ 

1 Byte Integer : **Target Star Red Component**

[0, 63] = Red Light Component of Target Star
___ 

1 Byte Integer : **Target Star Green Component**

[0, 63] = Green Light Component of Target Star
___ 

1 Byte Integer : **Target Star Blue Component**

[0, 63] = Blue Light Component of Target Star
___ 

1 Byte Integer : **Near Star Spin**

[?, ?] = Rotation Speed of Nearest Star
___ 

1 Byte Integer : **Near Star Red Component**

[0, 63] = Red Light Component of Nearest Star
___ 

1 Byte Integer : **Near Star Green Component**

[0, 63] = Green Light Component of Nearest Star
___ 

1 Byte Integer : **Near Star Blue Component**

[0, 63] = Blue Light Component of Nearest Star
___ 

1 Byte Integer : **Help Request Counter**

-1 = Error

0 = Inactive

[1, 63] = Beacon Progress
___ 

1 Byte Integer : **Menu Always On Flag**

1 = Always Render Menus
___ 

1 Byte Integer : **Depolarize Flag**

1 = Ship is Being Depolarized
___ 

1 Byte Integer : **Current Subsystem Flag**

1 = Flight Control

2 = Onboard Devices

3 = Preferences

4 = Screen Off
___ 

*Obsolete: Maintained for Compatibility*

2 Byte Integer : **Power**

[15000, 20000] = Elapsed Kilodyams Before Next Lithium Gram Injection
___ 

2 Byte Integer : **Subsystem Page**


0 = Onboard Devices

1 = Navigation Instruments

2 = Miscellaneous

3 = Galactic Cartography

4 = Emergency Functions
___ 

2 Byte Integer : **Target Star Class**

[0, 11] = Class of Selected Remote Target Star
___ 

*Obsolete: Maintained for Compatibility*

2 Byte Integer : **Fationic Cannon Distance**

? = Distance from Target at Fire Time
___ 

2 Byte Integer : **Near Star Class**

[0, 11] = Class of the Nearest Star
___ 

2 Byte Integer : **Number of Planets**

[0, 79] = Number of Planets in the Current System
___ 

4 Byte Float : **Player X Coordinate**

[-3100, 3100] = X Coordinate of Player Within Ship
___ 

4 Byte Float : **Player Y Coordinate**

? = Y Coordinate of Player Within Ship
___ 

4 Byte Float : **Player Z Coordinate**

[-300, -5800] = Z Coordinate of Player Within Ship
___ 

4 Byte Float : **Camera Alpha**

[-45, 45] = Yaw of Camera in Degrees
___ 

4 Byte Float : **Camera Beta**

[-90, 90] = Pitch of Camera in Degrees
___ 

4 Byte Float : **Navigation Beta**

[0, 360] = Ship Angle in Degrees
___ 

4 Byte Float : **Target Star Distance**

? = Distance in Nanoparsis to the Last Targeted Star
___ 

4 Byte Float : **Near Star Distance**

? = Distance in Nanoparsis to the Nearest Star
___ 

8 Byte Float : **Ship X Coordinate**

? = X Coordinate of Ship Within Galaxy
___ 

8 Byte Float : **Ship Y Coordinate**

? = Y Coordinate of Ship Within Galaxy
___ 

8 Byte Float : **Ship Z Coordinate**

? = Z Coordinate of Ship Within Galaxy
___ 

8 Byte Float : **Target Star X Coordinate**

? = X Coordinate of Last Targeted Star
___ 

8 Byte Float : **Target Star Y Coordinate**

? = Y Coordinate of Last Targeted Star
___ 

8 Byte Float : **Target Star Z Coordinate**

? = Z Coordinate of Last Targeted Star
___ 

8 Byte Float : **Near Star X Coordinate**

? = X Coordinate of Nearest Star
___ 

8 Byte Float : **Near Star Y Coordinate**

? = Y Coordinate of Nearest Star
___ 

8 Byte Float : **Near Star Z Coordinate**

? = Z Coordinate of Nearest Star
___ 

8 Byte Float : **Help Request Time**

? = Timestamp in Seconds Since Noctis Epoch When Help Request Will Be Satisfied
___ 

8 Byte Float : **Initial Target Distance**

? = Initial Distance from the Nearest Star
___ 

8 Byte Float : **Vimana Amplification**

? = ?
___ 

8 Byte Float : **Approach Coefficient**

? = ?
___ 

8 Byte Float : **Reaction Time**

? = ?
___ 

11 Bytes : **FCS Status**

"['?' x 10]\0" = Current FCS Readout
___ 

2 Byte Integer : **FCS Status Delay**

? = Duration in Clock Ticks of Last Message Displayed
___ 

2 Byte Integer : **Previous Subsystem**

0 = Onboard Devices

1 = Navigation Instruments

2 = Miscellaneous

3 = Galactic Cartography

4 = Emergency Functions
___ 

8 Byte Float : **AP Target Initial Distance**

? = Initial Distance from Remote Target
___ 

8 Byte Float : **Requested Vimana Coefficient**

? = ?
___

8 Byte Float : **Current Vimana Coefficient**

? = ?
___

8 Byte Float : **Vimana Reaction Time**

? = ?
___ 

1 Byte Integer : **Lithium Collector Flag**

1 = Currently Scoping Lithium
___ 

1 Byte Integer : **Auto Screen Off Flag**

1 = Screens Turn Off Automatically
___ 

1 Byte Integer : **AP Reached Flag**

? = Arrived in vicinity of local planet.
___ 

2 Byte Integer : **Lifter**

? = Delta Animating Player Y Position in Ship
___ 

8 Byte Float : **Seconds**

? = Seconds since Noctis Epoch (January 1, 1984)
___ 

1 Byte Integer : **Data Flag**

0 = No Data Window Displayed
1 = Displaying Remote Target Data
2 = Displaying Local Target Data
3 = Displaying External Environment Data
___ 

1 Byte Integer : **Surlight**

? = Brightness of HUD Outer Rim
___ 

245 Bytes : **Total Size**
