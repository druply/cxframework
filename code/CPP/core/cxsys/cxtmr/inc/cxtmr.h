#ifndef CXTMR_H_INCLUDED
#define CXTMR_H_INCLUDED

enum cxTmr_En {
    tmr1 = 0,
    tmr2,
    tmr3,
    tmr4,
    tmr5
};

typedef enum cxTmr_En cxTmr_T;

void cxtmrInit(void);
void cxtmrStart(cxTmr_T timer);
void cxtmrStop(cxTmr_T timer);
void cxtmrDeInit(void);
double cxtmrGetTimeStamp(cxTmr_T timer);

#endif // CXTMR_H_INCLUDED
