#include "main.h"
#include <chrono>

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

	pros::ADIDigitalOut piston ('A');
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
#define Motor_Port 1 
#define Motor_Port2 2
#define DIGITAL_SENSOR_PORT 'A'
#define EXPANSIONPNEUMATIC 'B'
#define IntakeMotor_PORT 3
#define IntakeMotor_PORT1 8
#define LEFT_WHEELS_PORT 4
#define RIGHT_WHEELS_PORT 5
#define LEFT_WHEELS_BACK_PORT 6
#define RIGHT_WHEELS_BACK_PORT 7
#define ROLLER_MOTOR_PORT 9
void turn_left() {
 pros::Task::delay(10);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Motor_Group left_drivetrain({right_wheels,right_wheels_back});
  pros::Motor_Group right_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group all_drivetrain({left_wheels,right_wheels,left_wheels_back,right_wheels_back});
right_drivetrain.move_velocity(300);
left_drivetrain.move_velocity(-300);
pros::delay(500);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
}
void turn_right() {
   pros::Task::delay(10);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Motor_Group left_drivetrain({right_wheels,right_wheels_back});
  pros::Motor_Group right_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group all_drivetrain({left_wheels,right_wheels,left_wheels_back,right_wheels_back});
  left_drivetrain.move_velocity(300);
  right_drivetrain.move_velocity(-300);
  pros::delay(500);
  left_drivetrain.move_velocity(0);
  right_drivetrain.move_velocity(0);
}
void spin_roller() {
	  pros::Motor roller (ROLLER_MOTOR_PORT, true);
	  roller.move_velocity(150);
	  pros::delay(500);
	  roller.move_velocity(0);
}
void move_bot_forward() {
   pros::Task::delay(10);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Motor_Group left_drivetrain({right_wheels,right_wheels_back});
  pros::Motor_Group right_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group all_drivetrain({left_wheels,right_wheels,left_wheels_back,right_wheels_back});
  all_drivetrain.move_velocity(300);
  pros::delay(500);
  all_drivetrain.move_velocity(0);
}
void autonomous() {
  pros::Task::delay(10);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::ADIDigitalOut pistonExpansion (EXPANSIONPNEUMATIC);
  pros::Motor_Group left_drivetrain({right_wheels,right_wheels_back});
  pros::Motor_Group right_drivetrain({left_wheels,left_wheels_back});
  pros::Motor_Group all_drivetrain({left_wheels,right_wheels,left_wheels_back,right_wheels_back});
  //Try code if methods don't work

/**
right_drivetrain.move_velocity(300);
left_drivetrain.move_velocity(-300);
pros::delay(500);
right_drivetrain.move_velocity(0);
left_drivetrain.move_velocity(0);
pros::delay(1);
*/
pistonExpansion.set_value(false);
left_drivetrain.move_velocity(450);
right_drivetrain.move_velocity(300);
pros::delay(500);
left_drivetrain.move_velocity(450);
right_drivetrain.move_velocity(300);
roller.move_velocity(180);
pros::delay(1000);
roller.move_velocity(0);
all_drivetrain.move_velocity(0);
pros::delay(1);
//Not useful anymore; drivetrain and roller activated at the same time
/**
roller.move_velocity(150);
pros::delay(500);
roller.move_velocity(0);
*/
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  pros::Motor Motor1 (Motor_Port, true);
  pros::Motor Motor2 (Motor_Port2);
  pros::ADIDigitalOut pistonFlywheel (DIGITAL_SENSOR_PORT);
  pros::ADIDigitalOut pistonExpansion (EXPANSIONPNEUMATIC);
  pros::Motor intake (IntakeMotor_PORT);
  pros::Motor intake1 (IntakeMotor_PORT1, true);
  pros::Motor left_wheels (LEFT_WHEELS_PORT);
  pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
  pros::Motor left_wheels_back (LEFT_WHEELS_BACK_PORT );
  pros::Motor right_wheels_back (RIGHT_WHEELS_BACK_PORT, true);
  pros::Motor roller (ROLLER_MOTOR_PORT, true);
  pros::Controller master (CONTROLLER_MASTER);
  bool isPressedExpansion = master.get_digital(DIGITAL_Y);
  bool isPressedFlywheel = master.get_digital(DIGITAL_B);
  //added to keep expansion from shooting out
  pistonExpansion.set_value(false);
  while (true) {
  pistonExpansion.set_value(false);
	isPressedExpansion = master.get_digital(DIGITAL_Y);
	isPressedFlywheel = master.get_digital(DIGITAL_B);

	if (master.get_digital(DIGITAL_R1)) {
    //Motor1 was moving at 100 to whoever made it 100; let me know if it was intentional
		Motor1.move_velocity(100);
		Motor2.move_velocity(100);
	} else {
		Motor1.move_velocity(0);
		Motor2.move_velocity(0);
	}

  if (master.get_digital(DIGITAL_L2)) {
      //intake.move(127); 
      roller.move(-50);
  } else {
      //intake.move(0);
      roller.move(0);
	}

	if (master.get_digital(DIGITAL_L1)) {
		//intake.move(-127);
		intake.move_velocity(-300);
	} else {
		//intake.move(0);
		intake.move_velocity(0);
	}

	if (master.get_digital(DIGITAL_R2)) {
		roller.move_velocity(100);
	} else {
		roller.move_velocity(0);
	}


//Reversed because pnuematics is weird
/**
	if(isPressedExpansion){
		pistonExpansion.set_value(true);
		pros::delay(2);
	} else if (!isPressedExpansion) {
		pistonExpansion.set_value(true);
	} */

	if (isPressedFlywheel) {
		pistonFlywheel.set_value(false);
		pros::delay(2);
	} else if (!isPressedFlywheel){
		pistonFlywheel.set_value(true);
	}    

	left_wheels.move(master.get_analog(ANALOG_LEFT_Y) * 1.5);
	left_wheels_back.move(master.get_analog(ANALOG_LEFT_Y) * 1.5);
  right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));
	right_wheels_back.move(master.get_analog(ANALOG_RIGHT_Y));
	
    pros::delay(2);
  }
}
