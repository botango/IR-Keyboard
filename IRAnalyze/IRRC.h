
#define K_THRESHOLD_HEADER_HIGH_MIN    144   // 9000 * 0.8 / 50
#define K_THRESHOLD_HEADER_HIGH_MAX    216   // 9000 * 1.2 / 50
#define K_THRESHOLD_HEADER_LOW_MIN      72   // 4500 * 0.8 / 50
#define K_THRESHOLD_HEADER_LOW_MAX     108   // 4500 * 1.2 / 50
#define K_THRESHOLD_HEADER_REP_LOW_MIN  36   // 2250 * 0.8 / 50
#define K_THRESHOLD_HEADER_REP_LOW_MAX  54   // 2250 * 1.2 / 50
#define K_THRESHOLD_STOP_LOW_MIN        72

#define S_THRESHOLD_HEADER_HIGH_MIN     38   // 2400 * 0.8 / 50
#define S_THRESHOLD_HEADER_HIGH_MAX     58   // 2400 * 1.2 / 50
#define S_THRESHOLD_HEADER_LOW_MIN       9   //  600 * 0.8 / 50
#define S_THRESHOLD_HEADER_LOW_MAX      14   //  600 * 1.2 / 50
#define S_THRESHOLD_CODE                18   //  900 / 50
#define S_THRESHOLD_STOP_LOW_MIN        72

#define P_THRESHOLD_HEADER_HIGH_MIN     56   // 3500 * 0.8 / 50
#define P_THRESHOLD_HEADER_HIGH_MAX     84   // 3500 * 1.2 / 50
#define P_THRESHOLD_HEADER_LOW_MIN      27   // 1700 * 0.8 / 50
#define P_THRESHOLD_HEADER_LOW_MAX      41   // 1700 * 1.2 / 50
#define P_THRESHOLD_STOP_LOW_MIN        72

typedef enum
{
  MODE_CHECK_HEADER = 0,
  MODE_ANALYZE,
  MODE_RECEIVED,
  MODE_REPEAT,
  MODE_REPEAT_RECEIVED,
  MODE_OVERFLOW = 0x10,
} modeStatus;

typedef enum
{
  TYPE_K = 0,
  TYPE_S,
  TYPE_P,
} typeStatus;

#define DISABLE_REPEAT_CODE
