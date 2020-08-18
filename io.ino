
///////////////////////
// IO1 state machine //
///////////////////////
void _IOSetup(void)
{
  in1State = IN_STATUS_INIT;
}

///////////////////////
// IO1 state machine //
///////////////////////
void _IO1Loop(void)
{
  switch (in1State)
  {
	  case IN_STATUS_INIT:
      in1TimeTick = millis();
      if (inAgua == IO_ON)
        in1State = IN_STATUS_ON;
      else
        in1State = IN_STATUS_OFF;

      break;
      
	  case IN_STATUS_ON:
      if (inAgua == IO_OFF)
        in1State = IN_STATUS_INIT;
      else
      {
        if (millis() - in1TimeTick >= timeoutSecInAgua)
        {
          // TODO
          //Indicar Alarma
        }
      }
      break;
      
	  case IN_STATUS_OFF:
      in1TimeTick = millis();
      if (inAgua == IO_ON)
        in1State = IN_STATUS_ON;

	    break;
  }
}
