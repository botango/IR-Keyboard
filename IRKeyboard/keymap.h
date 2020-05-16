#define MAX_BUTTON_DATA_BYTE_COUNT      8
#define MAX_DATA_BIT_COUNT              (MAX_BUTTON_DATA_BYTE_COUNT*8)
#define MAX_KEY_DATA_BYTE_COUNT         4

const uint8_t btn_data[][MAX_BUTTON_DATA_BYTE_COUNT+1]=
{
  {0} // end of btn_data
};

const uint8_t key_data[][MAX_KEY_DATA_BYTE_COUNT+1]=
{
	{0,0,0,0,0}
};
