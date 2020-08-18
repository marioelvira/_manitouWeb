
////////////////////
// Manitou set up //
////////////////////
void _ManitouSetup(void)
{
  //manitouNumberOfStarts;        // Read from E2PROM
  //manitouNumberOfHours          // Read from E2PROM
  manitouNumberOfOns2Save = 1;
  manitouNumberOfHours2Save = 1;
  manitouNumberOfHours2Increment = 1;
}

///////////////////////////
// Manitou state machine //
///////////////////////////
void _ManitouLoop(void)
{
  int eeprom_value_hi, eeprom_value_lo;
  
  if (inMotor == IO_ON)
  {
    // Si acabamos de arrancar
    if (manitouNumberOfOns2Save == 1)
    {
      manitouNumberOfOns++;
      
      // Save from E2PROM
      eeprom_value_lo = manitouNumberOfOns & 0x00FF;
      eeprom_value_hi = (manitouNumberOfOns & 0xFF00)>>8;
      EEPROM.write(EEPROM_ADD_NUMBEROF_ONS_LO, eeprom_value_lo);
      EEPROM.write(EEPROM_ADD_NUMBEROF_ONS_HI, eeprom_value_hi);     
      
      manitouNumberOfOns2Save = 0;
    }

    // Cada 10 minutos 
    if ((timeMin % 10) == 0)
    {
      // Incrementamos en decimas de hora
      if (manitouNumberOfHours2Increment == 1)
        manitouNumberOfHours++;

      manitouNumberOfHours2Increment = 0;
    }
    else
      manitouNumberOfHours2Increment = 1;

    // Cada 30 minutos
    if ((timeMin % 30) == 0)
    {      
      // Incrementamos en decimas de hora
      if (manitouNumberOfHours2Save == 1)
      {
        eeprom_value_lo = manitouNumberOfHours & 0x00FF;
        eeprom_value_hi = (manitouNumberOfHours & 0xFF00)>>8;
        EEPROM.write(EEPROM_ADD_NUMBEROF_HOURS_LO, eeprom_value_lo);
        EEPROM.write(EEPROM_ADD_NUMBEROF_HOURS_HI, eeprom_value_hi); 
      }
      
      manitouNumberOfHours2Save = 0;
    }
    else
      manitouNumberOfHours2Save = 1;
  }
  else
  {
    _ManitouSetup();
    _TimeSetup();
  }
}
