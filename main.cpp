#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(LeftFront, LeftMiddle, LeftBack),

//Right Motors:
motor_group(RightFront, RightMiddle, RightBack),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT19,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
357.6,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while(!auto_started){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
    Brain.Screen.printAt(5, 40, "Battery Percentage:");
    Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
    Brain.Screen.printAt(5, 100, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 120, "Selected Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 140, "Auton 1");
        break;
      case 1:
        Brain.Screen.printAt(5, 140, "Auton 2");
        break;
      case 2:
        Brain.Screen.printAt(5, 140, "Auton 3");
        break;
      case 3:
        Brain.Screen.printAt(5, 140, "Auton 4");
        break;
      case 4:
        Brain.Screen.printAt(5, 140, "Auton 5");
        break;
      case 5:
        Brain.Screen.printAt(5, 140, "Auton 6");
        break;
      case 6:
        Brain.Screen.printAt(5, 140, "Auton 7");
        break;
      case 7:
        Brain.Screen.printAt(5, 140, "Auton 8");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){ 
    case 0:
      progskills();
      break;
    case 1:         
      drive_test();
      break;
    case 2:
      turn_test();
      break;
    case 3:
      swing_test();
      break;
    case 4:
      full_test();
      break;
    case 5:
      odom_test();
      break;
    case 6:
      tank_odom_test();
      break;
    case 7:
      holonomic_odom_test();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    if(Controller.ButtonA.pressing()){

      IntakeBottom.setVelocity(100, percent);  
      IntakeTop.setVelocity(100, percent);
      descore.set(true);

      // drive towards loader, turn, put scraper down, drive into loader
      chassis.set_drive_exit_conditions(1.5, 300, 1500); //2000
      chassis.drive_distance(34, 0);
      chassis.set_turn_exit_conditions(1, 300, 1000);
      chassis.turn_to_angle(90);
      Scraper1.set(true);
      Scraper2.set(true);
      IntakeBottom.spin(reverse);
      wait(200, msec);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
      chassis.set_drive_constants(4, 1.5, 0, 10, 0);
      chassis.drive_distance(11.25, 90);
      //chassis.turn_to_angle(85);
      wait(1750, msec);

      // back away and drive to other side of field
      chassis.set_drive_constants(10, 1.5, 0, 10, 0);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
      chassis.drive_distance(-5);
      IntakeBottom.stop();
      IntakeTop.stop();
      Scraper1.set(false);
      Scraper2.set(false);
      chassis.set_turn_exit_conditions(1, 300, 1000);
      chassis.turn_to_angle(135);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
      chassis.drive_distance(-9, 135); 
      chassis.set_turn_exit_conditions(1, 300, 500);
      chassis.set_swing_exit_conditions(1, 300, 300);
      chassis.left_swing_to_angle(90);
      chassis.set_drive_exit_conditions(1.5, 300, 2500); //5000
      chassis.drive_distance(-68, 85);

      // line up with long goal and score
      chassis.set_turn_exit_conditions(1, 300, 500);
      //chassis.turn_to_angle(0);
      //chassis.right_swing_to_angle(-45);
      chassis.set_swing_exit_conditions(1, 300, 300);
      chassis.left_swing_to_angle(0);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
      chassis.drive_distance(-9, 0);//prev -10
      chassis.turn_to_angle(-90);
      chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
      chassis.drive_distance(-18, -90);
      IntakeBottom.spin(reverse);
      IntakeTop.spin(reverse);
      chassis.turn_to_angle(-90);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //1000
      chassis.drive_distance(-2, -90);
      wait(1750, msec);
      
      //drive into second loader, get blocks, score on long goal
      IntakeTop.stop(); 
      Scraper1.set(true);
      Scraper2.set(true);
      wait(200, msec);
      chassis.set_drive_constants(4, 1.5, 0, 10, 0);
      chassis.set_drive_exit_conditions(1.5, 300, 1500); //1500
      chassis.drive_distance(28.75, -90);
      wait(1500, msec);
      chassis.set_drive_constants(10, 1.5, 0, 10, 0);
      chassis.set_drive_exit_conditions(1.5, 300, 1500); //1500
      chassis.drive_distance(-31, -90);
      IntakeTop.spin(reverse);
      wait(1500, msec);
      chassis.turn_to_angle(-90);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //1500
      chassis.drive_distance(-2, -90);
      wait(1700, msec);
      //chassis.turn_to_angle(-90);

      //move accross field, line up with third loader, get blocks
      Scraper1.set(false);
      Scraper2.set(false);
      IntakeTop.stop(); 
      chassis.set_drive_exit_conditions(1.5, 300, 1000); //2000
      chassis.drive_distance(16, -90); //prev 17
      chassis.set_turn_exit_conditions(1, 300, 1000);
      chassis.turn_to_angle(-185);
      chassis.set_drive_exit_conditions(1.5, 300, 3500);
      chassis.drive_distance(97, -187);//prev 185
      chassis.turn_to_angle(-90);
      Scraper1.set(true);
      Scraper2.set(true);
      chassis.set_drive_constants(4, 1.5, 0, 10, 0);
      IntakeBottom.spin(reverse);
      chassis.set_drive_exit_conditions(1.5, 300, 1000); //3500
      chassis.drive_distance(15.5, -90);
      wait(1000, msec);//prev 1400
      chassis.turn_to_angle(-90);

      // back away and move to other side of field
      chassis.set_drive_constants(10, 1.5, 0, 10, 0);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //3500
      chassis.drive_distance(-5, -90);
      IntakeTop.stop();
      IntakeBottom.stop();
      Scraper1.set(false);
      Scraper2.set(false);
      chassis.turn_to_angle(-45);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //1000
      chassis.drive_distance(-11, -45);
      chassis.set_turn_exit_conditions(1, 300, 750);
      chassis.set_swing_exit_conditions(1, 300, 300);
      chassis.left_swing_to_angle(-90);
      chassis.set_drive_exit_conditions(1.5, 300, 2500); //2000
      chassis.drive_distance(-70, -85);

      //line up with long goal and score
      chassis.set_swing_exit_conditions(1, 300, 300);
      chassis.left_swing_to_angle(-180);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //1000
      chassis.drive_distance(-8, -180);
      chassis.turn_to_angle(-270);
      chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
      chassis.drive_distance(-18, -270);
      IntakeBottom.spin(reverse);
      IntakeTop.spin(reverse);
      chassis.turn_to_angle(90);
      wait(1900, msec);
      IntakeTop.stop();

      //get fourth loader and score
      Scraper1.set(true);
      Scraper2.set(true);
      chassis.set_drive_constants(4, 1.5, 0, 10, 0);
      chassis.set_drive_exit_conditions(1.5, 300, 1500); //1500
      chassis.drive_distance(28.75, -270);
      wait(1500, msec);
      chassis.set_drive_constants(10, 1.5, 0, 10, 0);
      chassis.set_drive_exit_conditions(1.5, 300, 1500); //1000
      chassis.drive_distance(-29.25, -270);
      IntakeTop.spin(reverse);
      chassis.turn_to_angle(90);
      wait(2100, msec);//prev 1900

      //park
      Scraper1.set(false);
      Scraper2.set(false);
      chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
      chassis.drive_distance(20, -270);
      chassis.turn_to_angle(45);
      chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
      chassis.drive_distance(17);
      chassis.right_swing_to_angle(10);
      chassis.set_drive_exit_conditions(1.5, 300, 500); //1000
      chassis.drive_distance(9, 10);
      Scraper1.set(true);
      Scraper2.set(true);
      IntakeTop.spin(reverse);
      IntakeBottom.spin(reverse);
      chassis.set_drive_exit_conditions(1.5, 300, 1500); //1000
      chassis.drive_distance(37, 5);//prev 40
      Scraper1.set(false);
      Scraper2.set(false);

    //   chassis.drive_distance(17);
    // chassis.turn_to_angle(90);
    // chassis.drive_distance(36);
    // chassis.turn_to_angle(225);
    }

    chassis.control_arcade();
    

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
