/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
    (C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
    (C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#include "Joystick.h"

/////////////////////////模块区/////////////////////////

//按键列表
//UP 左摇杆向上
//DOWN 左摇杆向下
//LEFT 左摇杆向左
//RIGHT 左摇杆向右
//UPLEFT 左摇杆向左上
//UPRIGHT 左摇杆向右上
//DOWNLEFT 左摇杆向左下
//DOWNRIGHT 左摇杆向右下
//X 按下X键
//Y 按下Y键
//A 按下A键
//B 按下B键
//L 按下L键
//R 按下R键
//ZL 按下ZL键
//ZR 按下ZR键
//PLUS 按下加号键
//MINUS 按下减号键
//HOME 按下HOME键
//LCLICK 按下左摇杆
//RCLICK 按下右摇杆
//PAUSE 暂停

//格式:{操作, 持续时间},
//持续时间40约等于1秒 上限200 超过的要拆开
//单击的持续时间最好写2 太短可能会不识别

//联网
static const command LianWang[] PROGMEM = {
    {B, 5},
    {Y, 2},
    {PAUSE, 50},
    {PLUS, 2},
    {PAUSE, 200}, //联网等待20秒
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {A, 2},
    {PAUSE, 5},
    {B, 2},
    {PAUSE, 40},
    {SCRIPT_END, 0},
};

//进坑
static const command JinKen[] PROGMEM = {
    {A, 2},
    {PAUSE, 240},//进坑6秒
    {SCRIPT_END, 0},
};

//招募
static const command ZhaoMu[] PROGMEM = {
    {A, 2},
    {PAUSE, 200},//等待2分钟
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {UP, 2},//等待最后10秒移动至准备
    {PAUSE, 200},
    {PAUSE, 200},
    {A, 2},
    {PAUSE, 20},
    {A, 2},
    {PAUSE, 20},
    {A, 2},
    {PAUSE, 30},
    {A, 2},
    {PAUSE, 30},
    {A, 2},
    {PAUSE, 30},
    {SCRIPT_END, 0},
};

//进场
static const command JinChang[] PROGMEM = {
    {PAUSE, 200},//等待30秒进入动画
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {PAUSE, 200},
    {A, 2},
    {PAUSE, 5},
    {A, 2},
    {PAUSE, 15},
    {A, 2},
    {PAUSE, 20},
    {A, 2},
    {PAUSE, 40},
    {SCRIPT_END, 0},
};

//退场
static const command TuiChang[] PROGMEM = {
    {HOME, 50},
    {DOWN, 2},
    {PAUSE, 5},
    {DOWN, 2},
    {PAUSE, 5},
    {DOWN, 2},
    {PAUSE, 5},
    {DOWN, 2},
    {PAUSE, 5},
    {A, 2},
    {PAUSE, 10},
    {A, 2},
    {PAUSE, 10},
    {B, 2},
    {PAUSE, 20},
    {A, 2},
    {PAUSE, 5},
    {SCRIPT_END, 0},
};

//可继续添加模块 别忘了结尾处的SCRIPT_END
//static const command NewScript[] PROGMEM = {
//    {SCRIPT_END, 0},
//};

/////////////////////////程序区/////////////////////////

//RunScript(模块名,执行次数)
//RunStep(单个操作,持续时间) 持续时间40约等于一秒
//LOOP_START(X) LOOP_END 之间的代码循环X次后继续 X=0为无限循环
//PROGRAM_END 程序结束后自动停止 如果不写 结束后会重复执行下去

char Password[] = "3729"; //输入密码

//开始
void AutoDrive()
{
LOOP_START(0)
  Drive();
  RunStep(PAUSE,200); //飞行断开等待5秒后重开
LOOP_END
PROGRAM_END
}

void Drive()
{
  RunScript(LianWang, 1);
  RunScript(JinKen, 1);
  RunStep(PLUS, 2);
  RunStep(PAUSE, 30);
  RunStep(RIGHT, 2);
  RunStep(PAUSE, 5);
  RunStep(DOWN, 2);
  RunStep(PAUSE, 5);
  InputPW();
  RunStep(PLUS, 2);
  RunStep(PAUSE, 40);
  RunStep(A, 2);
  RunStep(PAUSE, 30);
  RunScript(ZhaoMu, 1);
  RunScript(JinChang, 1);
  RunScript(TuiChang, 1);
}

void InputPW()
{
  for (int i = 0; i < 4 ; i++)
    {
      switch (Password[i])
          {
          case '0':
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            break;
          case '1':
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            RunStep(LEFT, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(RIGHT, 2);
            RunStep(PAUSE, 5);
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            break;
          case '2':
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            break;
          case '3':
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            RunStep(RIGHT, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(LEFT, 2);
            RunStep(PAUSE, 5);
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            break;
          case '4':
            RunStep(LEFT, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(RIGHT, 2);
            RunStep(PAUSE, 5);
            break;
          case '5':
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            break;
          case '6':
            RunStep(RIGHT, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(LEFT, 2);
            RunStep(PAUSE, 5);
            break;
          case '7':
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            RunStep(LEFT, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(RIGHT, 2);
            RunStep(PAUSE, 5);
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            break;
          case '8':
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            break;
          case '9':
            RunStep(DOWN, 2);
            RunStep(PAUSE, 5);
            RunStep(RIGHT, 2);
            RunStep(PAUSE, 5);
            RunStep(A, 2);
            RunStep(PAUSE, 5);
            RunStep(LEFT, 2);
            RunStep(PAUSE, 5);
            RunStep(UP, 2);
            RunStep(PAUSE, 5);
            break;

          default:
            break;
          }
    }
}

//输出A
void PressA()
{
  RunStep(A, 2);
  RunStep(PAUSE, 5);
}

//可继续添加程序 别忘了修改后面标记的两个地方
//void NewProgram()
//{
//  DoSomething;
//}

/////////////////////////函数区/////////////////////////

char STOP = 0;          //默认停止状态 作独立固件使用时将值改为0即为即插即用
char press = 0;         //按键动作
char ScriptNum = 1;     //脚本编号
char Stopping = 0;      //停止信号 用于逐层返回主循环并重新选择脚本
char LEDON = 0;         //LED开启状态
int LED = 74;           //LED计时器
int press_duration = 0; //按键时长计时器

int main(void)
{

  SetupHardware();

  GlobalInterruptEnable();

  for (;;)
  {
    Stopping = 0;
    //添加/删除脚本时需要依次添加/删除case项
    //默认运行1 作独立固件使用时修改case1为想要的脚本即可
    switch (ScriptNum)
    {
    case 1:
      AutoDrive();
      break;
    case 2:
      Drive();
      break;
    case 3:
      InputPW();
      break;
    case 4:
      PressA();
      break;

    default:
      break;
    }
  }
}

//切换脚本
void SwitchScript()
{
  //添加/删除脚本时需要修改上限7为现有脚本数
  if (ScriptNum != 4)
    ScriptNum++;
  else
    ScriptNum = 1;
  LED = ScriptNum * 15 + 59;
}

/////////////////////////无需修改/////////////////////////

//设置引脚状态
void SetupPIN()
{
  reset_bit(DDRD, 3);
  set_bit(PORTD, 3);
}

//LED闪烁
void FlashLED()
{
  set_bit(DDRD, 4);
  reset_bit(PORTD, 4);
  LEDON = 1;
}

//启停
void StopScript()
{
  STOP = !STOP;
  if (!STOP)
    Stopping = 1;
}

//按键检测
void PressButton()
{
  if (!read_bit(PIND, 3))
  {
    press = 1;
    press_duration++;
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(10);
  }
  if (press == 1)
  {
    if (read_bit(PIND, 3) && press_duration < 5)
    {
      press = 0;
      press_duration = 0;
      _delay_ms(10);
      _delay_ms(10);
      if (STOP)
      {
        SwitchScript();
      }
    }
    else if (read_bit(PIND, 3))
    {
      press = 0;
      press_duration = 0;
      _delay_ms(10);
      _delay_ms(10);
      StopScript();
    }
  }
}

//切换LED
void SwitchLED()
{
  if (LEDON)
  {
    reset_bit(DDRD, 4);
    LEDON = 0;
  }

  if (!STOP)
  {
    set_bit(DDRD, 5);
    reset_bit(PORTD, 5);
  }
  else
    reset_bit(DDRD, 5);

  if (LED)
  {
    if (LED%15==0&&LED>59)
      FlashLED();
    LED--;
  }
  else
    LED = ScriptNum * 15 + 59;
}

//运行指令
void RunStep(Buttons_t button, uint16_t duration)
{
  if (Stopping)
    return;
  for (; duration > 0; duration--)
  {
    PressButton();
    SwitchLED();
    if (Stopping)
      break;
    HID_Task(button);
    USB_USBTask();
    _delay_ms(10);
    _delay_ms(10);
    _delay_ms(4);
  }
}

//读取模块
void RunScript(command script[], int times)
{
  if (Stopping)
    return;
  for (; times > 0; times--)
  {
    for (int i = 0;; i++)
    {
      if (pgm_read_byte(&script[i].button) == SCRIPT_END)
      {
        break;
      }
      RunStep(pgm_read_byte(&script[i].button), pgm_read_byte(&script[i].duration));
      if (Stopping)
        break;
    }
    if (Stopping)
      break;
  }
}

void SetupHardware(void)
{
  // We need to disable watchdog if enabled by bootloader/fuses.
  MCUSR &= ~(1 << WDRF);
  wdt_disable();

  // We need to disable clock division before initializing the USB hardware.
  //clock_prescale_set(clock_div_1);
  // We can then initialize our hardware and peripherals, including the USB stack.
  /*
  #ifdef ALERT_WHEN_DONE
  // Both PORTD and PORTB will be used for the optional LED flashing and buzzer.
  #warning LED and Buzzer functionality enabled. All pins on both PORTB and \
           PORTD will toggle when printing is done.
  DDRD  = 0xFF; //Teensy uses PORTD
  PORTD =  0x0;
                  //We'll just flash all pins on both ports since the UNO R3
  DDRB  = 0xFF; //uses PORTB. Micro can use either or, but both give us 2 LEDs
  PORTB =  0x0; //The ATmega328P on the UNO will be resetting, so unplug it?
  #endif
  // The USB stack should be initialized last.
*/
  SetupPIN();

  USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void)
{
  // We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void)
{
  // We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void)
{
  bool ConfigSuccess = true;

  // We setup the HID report endpoints.
  ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
  ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

  // We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void)
{
  // We can handle two control requests: a GetReport and a SetReport.

  // Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(Buttons_t button)
{

  // If the device isn't connected and properly configured, we can't do anything here.
  if (USB_DeviceState != DEVICE_STATE_Configured)
    return;

  // We'll start with the OUT endpoint.
  Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
  // We'll check to see if we received something on the OUT endpoint.
  if (Endpoint_IsOUTReceived())
  {
    // If we did, and the packet has data, we'll react to it.
    if (Endpoint_IsReadWriteAllowed())
    {
      // We'll create a place to store our data received from the host.
      USB_JoystickReport_Output_t JoystickOutputData;
      // We'll then take in that data, setting it up in our storage.
      while (Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError)
        ;
      // At this point, we can react to this data.

      // However, since we're not doing anything with this data, we abandon it.
    }
    // Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
    Endpoint_ClearOUT();
  }

  // We'll then move on to the IN endpoint.
  Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
  // We first check to see if the host is ready to accept data.
  if (Endpoint_IsINReady())
  {
    // We'll create an empty report.
    USB_JoystickReport_Input_t JoystickInputData;
    // We'll then populate this report with what we want to send to the host.
    GetNextReport(&JoystickInputData, button);
    // Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
    while (Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError)
      ;
    // We then send an IN packet on this endpoint.
    Endpoint_ClearIN();
  }
}

typedef enum
{
  SYNC_CONTROLLER,
  BREATHE,
  PROCESS,
} State_t;

State_t state = SYNC_CONTROLLER;

USB_JoystickReport_Input_t last_report;

int report_count = 0;
int hold_LX = STICK_CENTER;
int hold_LY = STICK_CENTER;
int hold_RX = STICK_CENTER;

void GetNextReport(USB_JoystickReport_Input_t *const ReportData, Buttons_t button)
{
  //按键释放
  memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
  ReportData->LX = STICK_CENTER;
  ReportData->LY = STICK_CENTER;
  ReportData->RX = STICK_CENTER;
  ReportData->RY = STICK_CENTER;
  ReportData->HAT = HAT_CENTER;

  //Hold stick
  ReportData->LX = hold_LX;
  ReportData->LY = hold_LY;
  ReportData->RX = hold_RX;

  // States and moves management
  switch (state)
  {
  case SYNC_CONTROLLER:
    state = BREATHE;
    break;

  case BREATHE:
    state = PROCESS;
    Stopping = 1;
    break;

  case PROCESS:
    if (!STOP)
    {
      switch (button)
      {
      case UP:
        ReportData->LY = STICK_MIN;
        break;

      case LEFT:
        ReportData->LX = STICK_MIN;
        break;

      case DOWN:
        ReportData->LY = STICK_MAX;
        break;

      case RIGHT:
        ReportData->LX = STICK_MAX;
        break;

      case UPLEFT:
        ReportData->LY = STICK_MIN;
        ReportData->LX = STICK_MIN;
        break;

      case UPRIGHT:
        ReportData->LY = STICK_MIN;
        ReportData->LX = STICK_MAX;
        break;

      case DOWNLEFT:
        ReportData->LY = STICK_MAX;
        ReportData->LX = STICK_MIN;
        break;

      case DOWNRIGHT:
        ReportData->LY = STICK_MAX;
        ReportData->LX = STICK_MAX;
        break;

      case HOLD_UP:
        hold_LY = STICK_MIN;
        break;

      case HOLD_LEFT:
        hold_LX = STICK_MIN;
        break;

      case HOLD_DOWN:
        hold_LY = STICK_MAX;
        break;

      case HOLD_RIGHT:
        hold_LX = STICK_MAX;
        break;

      case HOLD_CLEAR:
        hold_LX = STICK_CENTER;
        hold_LY = STICK_CENTER;
        break;

      case HOLD_CAM_L:
        hold_RX = STICK_MIN;
        break;

      case HOLD_CAM_R:
        hold_RX = STICK_MAX;
        break;

      case HOLD_CAM_C:
        hold_RX = STICK_CENTER;
        break;

      case A:
        ReportData->Button |= SWITCH_A;
        break;

      case B:
        ReportData->Button |= SWITCH_B;
        break;

      case X:
        ReportData->Button |= SWITCH_X;
        break;

      case Y:
        ReportData->Button |= SWITCH_Y;
        break;

      case L:
        ReportData->Button |= SWITCH_L;
        break;

      case R:
        ReportData->Button |= SWITCH_R;
        break;

      case ZL:
        ReportData->Button |= SWITCH_ZL;
        break;

      case ZR:
        ReportData->Button |= SWITCH_ZR;
        break;

      case PLUS:
        ReportData->Button |= SWITCH_PLUS;
        break;

      case MINUS:
        ReportData->Button |= SWITCH_MINUS;
        break;

      case HOME:
        ReportData->Button |= SWITCH_HOME;
        break;

      case LCLICK:
        ReportData->Button |= SWITCH_LCLICK;
        break;

      case RCLICK:
        ReportData->Button |= SWITCH_RCLICK;
        break;

      default:
        break;
      }
    }
  }

  // Prepare to echo this report
  memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
  //  echoes = ECHOES;
}
