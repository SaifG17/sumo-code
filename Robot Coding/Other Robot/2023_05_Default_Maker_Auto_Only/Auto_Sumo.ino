
void run_starting_move() {

  //REMEMBER BINARY NO
  //---0-0-0----Mode 0
  //---0-0-1----Mode 1
  //---0-1-0----Mode 2
  //---0-1-1----Mode 3
  //---1-0-0----Mode 4
  //---1-0-1----Mode 5
  //---1-1-0----Mode 6
  //---1-1-1----Mode 7

  Serial.println(read_dip_mode());

  if (read_dip_mode() == 0) {
    //do nothing
  }


  else if (read_dip_mode() == 1) {

    //Right side by Right Side
    motorsteer("leftatC", 200);
    delay(90);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);
  }


  else if (read_dip_mode() == 2) {
    //Left side by Left Side
    motorsteer("rightatC", 200);
    delay(90);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);
  }


  else if (read_dip_mode() == 3) {

    //Half Moon from Right
    motorsteer("rightatC", 200);
    delay(70);

    //enable when you want to use stop, disable when already done tuning

    //motordrive("forward",  0, "forward", 0);  delay(1000);


    motordrive("forward", 80, "forward", 150);
    delay(200);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);

    motordrive("forward", 50, "forward", 150);
    delay(300);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);
  }


  else if (read_dip_mode() == 4) {
    //Half Moon from Left
    motorsteer("leftatC", 200);
    delay(70);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);

    motordrive("forward", 150, "forward", 80);
    delay(200);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);

    motordrive("forward", 150, "forward", 50);
    delay(300);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);
  }


  else if (read_dip_mode() == 5) {
    //Back to Back
    motorsteer("rightatC", 200);
    delay(180);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);
  }


  else if (read_dip_mode() == 6) {
    //reserved
    //Back to Back
    motorsteer("rightatC", 200);
    delay(180);
    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);

    motorsteer("forward", 200);
    delay(150);

    //enable when you want to use stop, disable when already done tuning
    //motordrive("forward",  0, "forward", 0);  delay(1000);

  }


  else if (read_dip_mode() == 7) {
    //reserved


  }



  else {
  }
}



void run_auto_sumo() {


  while (1) {

    // Serial.print(speed_mode);
    // Serial.print("\t");
    // Serial.print(speed_normal);
    // Serial.print("\t");
    // Serial.println(speed_new);

    read_edge();
    if (ed_L == 0) {

      motorsteer("backward", 100);
      delay(1000);
      // motorsteer("rightatC", 150);
      // delay(100);

      speed_new = speed_normal;
      speed_mode = 0;

    } else if (ed_R == 0) {

      motorsteer("backward", 100);
      delay(1000);
      // motorsteer("leftatC", 150);
      // delay(100);

      speed_new = speed_normal;
      speed_mode = 0;

    } else {

      if (digitalRead(pin_FC) == 0) {

        if (speed_mode == 0) {

          speed_new = speed_new + speed_inc;
          delay(30);
          Serial.println("mode 0");

          if (speed_new >= 100) {
            speed_mode = 1;
            //  Serial.println("change to mode 1");
            // delay(1000);
          }
        }

        if (speed_mode == 1) {
          speed_new = speed_new + speed_inc_2;
          Serial.println("mode 1");
          if (speed_new >= 255) {
            speed_new = 255;
          }
        }

        motorsteer("forward", speed_new);
      }

      else if (digitalRead(pin_L) == 0) {
        motorsteer("leftatC", 200);
        delay(100);
        speed_new = speed_normal;
        speed_mode = 0;

        //enable when you want to use stop, disable when already done tuning
        //motordrive("forward",  0, "forward", 0);  delay(1000);
      }

      else if (digitalRead(pin_FL) == 0) {
        motordrive("forward", 20, "forward", 150);
        speed_new = speed_normal;
        speed_mode = 0;
      }

      else if (digitalRead(pin_FR) == 0) {
        motordrive("forward", 150, "forward", 20);
        speed_new = speed_normal;
        speed_mode = 0;
      }

      else if (digitalRead(pin_R) == 0) {
        motorsteer("rightatC", 200);
        delay(100);
        speed_new = speed_normal;
        speed_mode = 0;

        //enable when you want to use stop, disable when already done tuning
        //motordrive("forward",  0, "forward", 0);  delay(1000);
      }

      else {
        // Adjust speed kiri & kanan klau robot bergerak secara curve
        // robot bergerak pada kelajuan ini sehingga menjumpai objek
        speed_new = speed_normal;
        speed_mode = 0;

        motordrive("forward", speed_normal, "forward", speed_normal);
      }
    }
  }
}
