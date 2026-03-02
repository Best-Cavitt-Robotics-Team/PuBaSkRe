
#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 2000);
  chassis.set_turn_exit_conditions(1, 300, 1000);
  chassis.set_swing_exit_conditions(1, 300, 500);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

void progskills(){
  IntakeBottom.setVelocity(100, percent);  
  IntakeTop.setVelocity(100, percent);
  descore.set(true);

  // drive towards loader, turn, put scraper down, drive into loader
  chassis.set_drive_exit_conditions(1.5, 300, 1500); //2000
  chassis.drive_distance(34, 0);
  wait(50, msec);
  chassis.set_turn_exit_conditions(1, 300, 1000);
  chassis.turn_to_angle(90);
  wait(50, msec);
  Scraper1.set(true);
  Scraper2.set(true);
  IntakeBottom.spin(reverse);
  wait(200, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.drive_distance(10.25, 90); //prev 11.25
  wait(50, msec);
  //chassis.turn_to_angle(85);
  wait(1750, msec);

  // back away and drive to other side of field
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
  chassis.drive_distance(-5);
  wait(50, msec);
  IntakeBottom.stop();
  IntakeTop.stop();
  Scraper1.set(false);
  Scraper2.set(false);
  chassis.set_turn_exit_conditions(1, 300, 1000);
  chassis.turn_to_angle(135);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
  chassis.drive_distance(-12, 135);  //pev -9 mirror later
  wait(50, msec);
  chassis.set_turn_exit_conditions(1, 300, 500);
  chassis.set_swing_exit_conditions(1, 300, 500);
  chassis.left_swing_to_angle(90);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 2500); //5000
  chassis.drive_distance(-68, 85);
  wait(50, msec);

  // line up with long goal and score
  chassis.set_turn_exit_conditions(1, 300, 500);
  //chassis.turn_to_angle(0);
  //chassis.right_swing_to_angle(-45);
  chassis.set_swing_exit_conditions(1, 300, 500);
  chassis.left_swing_to_angle(0);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //2000
  chassis.drive_distance(-7, 0);//prev -9
  wait(50, msec);
  chassis.turn_to_angle(-90);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
  chassis.drive_distance(-18, -90);
  wait(50, msec);
  IntakeBottom.spin(reverse);
  IntakeTop.spin(reverse);
  chassis.turn_to_angle(-90);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //1000
  chassis.drive_distance(-2, -90);
  wait(50, msec);
  wait(1750, msec);
  
  //drive into second loader, get blocks, score on long goal
  IntakeTop.stop(); 
  Scraper1.set(true);
  Scraper2.set(true);
  wait(200, msec);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1500); //1500
  chassis.drive_distance(28.75, -88);//prev -90 degeress
  // wait(50, msec);
  wait(1500, msec);
  chassis.set_drive_constants(5, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1000); //prev 1500
  chassis.drive_distance(-31, -91);//prev -90 degrees
  wait(50, msec);
  IntakeTop.spin(reverse);
  wait(1500, msec);
  chassis.turn_to_angle(-90);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //1500
  chassis.drive_distance(-2, -90);
  wait(50, msec);
  wait(1700, msec);
  //chassis.turn_to_angle(-90);

  //move accross field, line up with third loader, get blocks
  Scraper1.set(false);
  Scraper2.set(false);
  IntakeTop.stop(); 
  chassis.set_drive_exit_conditions(1.5, 300, 1000); //2000
  chassis.drive_distance(16, -90); //prev 17
  wait(50, msec);
  chassis.set_turn_exit_conditions(1, 300, 1000);
  chassis.turn_to_angle(-180);//prev 185
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 3500);
  chassis.drive_distance(96, -180);//prev 185 and 97
  wait(50, msec);
  chassis.turn_to_angle(-90);//prev -90  
  Scraper1.set(true);
  Scraper2.set(true);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  IntakeBottom.spin(reverse);
  chassis.set_drive_exit_conditions(1.5, 300, 1000); //3500
  chassis.drive_distance(-30, -90);
  wait(50, msec);
  chassis.turn_to_angle(-88);
  wait(50, msec);
  chassis.drive_distance(25, -88);//prev 30.75
  wait(1500, msec);//prev 1400
  chassis.turn_to_angle(-90);
  wait(50, msec);

  // back away and move to other side of field
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //3500
  chassis.drive_distance(-5, -90);
  wait(50, msec);
  IntakeTop.stop();
  IntakeBottom.stop();
  Scraper1.set(false);
  Scraper2.set(false);
  chassis.turn_to_angle(-45);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //1000
  chassis.drive_distance(-12, -45); //pev -11
  wait(50, msec);
  chassis.set_turn_exit_conditions(1, 300, 750);
  chassis.set_swing_exit_conditions(1, 300, 500);
  chassis.left_swing_to_angle(-90);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 2500); //2000
  chassis.drive_distance(-70, -85);
  wait(50, msec);

  //line up with long goal and score
  chassis.set_swing_exit_conditions(1, 300, 500);
  chassis.left_swing_to_angle(-180);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 750); //prev 500 before 1000
  chassis.drive_distance(-10, -180);//prev -8
  wait(50, msec);
  chassis.turn_to_angle(-270);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
  chassis.drive_distance(-18, -270);
  wait(50, msec);
  IntakeBottom.spin(reverse);
  IntakeTop.spin(reverse);
  chassis.turn_to_angle(90);
  wait(50, msec);
  wait(1900, msec);
  IntakeTop.stop();

  //get fourth loader and score
  Scraper1.set(true);
  Scraper2.set(true);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1500); //1500
  chassis.drive_distance(28.75);//prev had angle of -270
  wait(50, msec);
  wait(1500, msec);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 1500); //1000
  chassis.turn_to_angle(87);
  wait(50, msec);
  chassis.drive_distance(-29.25, 87);//prev had angle of -270
  wait(50, msec);
  IntakeTop.spin(reverse);
  chassis.turn_to_angle(90);
  wait(2100, msec);//prev 1900

  //park
  Scraper1.set(false);
  Scraper2.set(false);
  chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
  chassis.drive_distance(20, -270);
  wait(50, msec);
  chassis.turn_to_angle(45);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 1000); //1000
  chassis.drive_distance(17);
  wait(50, msec);
  chassis.right_swing_to_angle(10);
  wait(50, msec);
  chassis.set_drive_exit_conditions(1.5, 300, 500); //1000
  chassis.drive_distance(9, 10);
  wait(50, msec);
  Scraper1.set(true);
  Scraper2.set(true);
  IntakeTop.spin(reverse);
  IntakeBottom.spin(reverse);
  chassis.set_drive_exit_conditions(1.5, 300, 1500); //1000
  chassis.drive_distance(43, 5);//prev 40
  Scraper1.set(false);
  Scraper2.set(false);

//   chassis.drive_distance(17);
// chassis.turn_to_angle(90);
// chassis.drive_distance(36);
// chassis.turn_to_angle(225);



}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}
