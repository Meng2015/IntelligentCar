/*  <The 14th National University Students Intelligent Car Race.>
 *  Copyright (C) <2019>  < github.com:He0L1w  NJUST >
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "system.h"


/* 基于阿克曼半径的方向控制 */

void car_direction_control(void)
{
  char txt[16];
  double R;
  double arc_err;
  uint16_t servo_pwm;
  
  R = calculate_Ackman_R(img.cal_ops->transform(120,midline[120]));

  /* 外层判断偏差方向 */
  if ( R<0 && R>-200 )
  {/* 内层根据偏差进行分段比例控制 */
    arc_err = 200 + R;
    if (arc_err<=90)
      servo_pwm = (uint16_t)(SERVO_MID - 1.4*arc_err);
    else if(arc_err>90 && arc_err<=140)
      servo_pwm = (uint16_t)(SERVO_MID - 2*arc_err);
    else
      servo_pwm = (uint16_t)(SERVO_MID - 5*arc_err);
  }
  else if (R>0 && R<200)
  {
    arc_err = 200 - R;
    if (arc_err<=90)
      servo_pwm = (uint16_t)(SERVO_MID + 1.4*arc_err);
    else if (arc_err>90 && arc_err<=140)
      servo_pwm = (uint16_t)(SERVO_MID + 2*arc_err);
    else
      servo_pwm = (uint16_t)(SERVO_MID + 5*arc_err);
  }
  else
    servo_pwm = SERVO_MID;
  
  servo(servo_pwm);
  
  sprintf(txt, "PWM: %4d", servo_pwm);
  LCD_P6x8Str(0,0,(uint8_t*)txt); 
  sprintf(txt, "R:  %5.2f", R);
  LCD_P6x8Str(0,1,(uint8_t*)txt);  
}


