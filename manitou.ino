
////////////////////
// Manitou set up //
////////////////////
void _ManitouSetup(void)
{
  manitouNumberOfStarts = 0;  // TODO Read from E2PROM
  manutouJustStart = 1;
  manitouNumberOfHours = 0;   // TODO Read from E2PROM
}

///////////////////////////
// Manitou state machine //
///////////////////////////
void _ManitouLoop(void)
{
  if (inMotor == IO_ON)
  {
    // Si acabamos de arrancar
    if (manutouJustStart == 1)
    {
      manitouNumberOfStarts++;
      // TODO Save from E2PROM
      manutouJustStart = 0;
    }

    // Cada hora
    /*
    //if ()
    {
      // TODO Read from E2PROM
      //manitouNumberOfHours = EEPROM.read(EEPROM_NUMBER_OF_HOURS_HIGH);
      //manitouNumberOfHours = EEPROM.read(EEPROM_NUMBER_OF_HOURS_LOW);
      manitouNumberOfHours++; 
      // TODO Write on E2PROM
      //EEPROM.write(EEPROM_NUMBER_OF_HOURS_HIGH, manitouNumberOfHours);
      //EEPROM.write(EEPROM_NUMBER_OF_HOURS_LOW,  manitouNumberOfHours);
    }
    */
  }
  else
  {
    manutouJustStart = 1;
    _TimeSetup();
  }
}
