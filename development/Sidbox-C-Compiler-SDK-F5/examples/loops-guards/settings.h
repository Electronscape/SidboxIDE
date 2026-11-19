#ifndef SIDC_DEMO_SETTINGS_H
#define SIDC_DEMO_SETTINGS_H
#define FEATURE_LOOP 1
#define LOOP_BONUS 7
#define STEP 2
#define FEATURE_MASK (1 << 2)
#if (FEATURE_LOOP && defined(LOOP_BONUS) && (LOOP_BONUS >= 7) && (FEATURE_MASK & 4))
int calculate(void);
#elif defined(OTHER_FEATURE)
int unsupported_branch(void);
#else
int missing_branch(void);
#endif
#endif /* SIDC_DEMO_SETTINGS_H */
