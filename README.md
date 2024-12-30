### How to Use？

### Step1建立刚体
在动捕的电脑上选择无人机，建立刚体并完成命名。
**建立刚体时无人机机头需要朝向与动捕X轴相同的方向**
### Step2 无人机连接动捕 WiFi
容易出现无人机自动连接其他WIFI，可以把其他Wifi暂时忘记密码。
### Step3 在无人机记载电脑运行Launch文件
`roslaunch odom_publisher_node use_moncap.launch `
其中Launch文件如下，需要注意修改参数**rigid_name**为自己的名称
```
<launch>
    <!-- Step1:修改为自己的刚体名称，注意建立刚体时机头朝向！！ -->

    <arg name="rigid_name" default="uav1" />

    <!-- Step2:启动vrpn_client_ros -->

    <include file="$(find vrpn_client_ros)/launch/sample.launch">
        <arg name="server" value="192.168.1.1"/>
    </include>

    <!-- Step3:启动 mavros -->

    <include file="$(find mavros)/launch/px4.launch">
        <arg name="fcu_url" value="/dev/ttyACM0:57600" />
	    <!-- <arg name="gcs_url" value="udp-b://@"/> -->
        <!-- here you can choose the QGC'ip for connect -->
	    <arg name="tgt_system" value="3" />
    </include>

    <!-- Step4: 映射话题-->
    <node 
        name="relay_vrpn_node" 
        pkg="topic_tools" type="relay" 
        args="/vrpn_client_node/$(arg rigid_name)/pose /mavros/vision_pose/pose" 
        output="screen"
    />

    <!--（可选） Step5: 融合里程计。动捕没有里程计信息，手动融合，发布话题为/vision_odom-->
    <node   
        name="odom_publisher_node"
        pkg="odom_publisher_node" 
        type="odom_publisher_node"  
        output="screen" >
        <remap from="/vrpn_client_node/uav1/pose" to="/vrpn_client_node/$(arg rigid_name)/pose"/>
        <remap from="/vrpn_client_node/uav1/twist" to="/vrpn_client_node/$(arg rigid_name)/twist"/>
    </node> 
    
    <!--（可选） Step6: 增加IMU和Odom的发布频率-->
    <node 
        name="mavcmd_imu" 
        pkg="mavros" 
        type="mavcmd" 
        args="long 511 105 5000 0 0 0 0 0 " 
        output="screen"
    />

    <node 
        name="mavcmd_odom" 
        pkg="mavros" 
        type="mavcmd" 
        args="long 511 31 5000 0 0 0 0 0 " 
        output="screen"
    />
</launch>
```
