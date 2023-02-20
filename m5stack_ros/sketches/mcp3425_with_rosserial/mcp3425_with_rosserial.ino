#define M5STACK_ATOM
#include <m5stack_ros.h>
#include <std_msgs/Float32.h>

#define MCP3425_address 0x68
#define configRegister 0b10011000 //16bit 15sps PGA x1 

std_msgs::Float32 msg;
ros::Publisher voltage_pub("voltage", &msg);

void setup() {
  setupM5stackROS("M5Stack ROS mcp3425");
  Wire.begin(26,32);
  Wire.beginTransmission(MCP3425_address);
  Wire.write(configRegister);
  Wire.endTransmission();

  nh.advertise(voltage_pub);
}

void loop() {
  float vol = (int16_t)readADC() * 2.048 / 32767.0 ;
  if (fabs(vol) > 3.3) {
    vol = 0;
  }
  msg.data = vol;
  voltage_pub.publish(&msg);
  nh.spinOnce();
  delay(100);
}

float readADC() {
  Wire.requestFrom(MCP3425_address, 2);
  return ( (Wire.read() << 8 ) + Wire.read() );
}
