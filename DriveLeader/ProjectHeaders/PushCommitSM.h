#ifndef PushCommitSM_H
#define PushCommitSM_H

typedef enum {
    BACK_UP_A_BIT,
    ROTATE_TO_FACE_BRANCH,
            STOP_PUSH_COMMIT,
            MOVE_FORWARD,
            FORWARD_A_BIT
} PushCommitSMState_t;

ES_Event_t RunPushCommitSM(ES_Event_t CurrentEvent);
void StartPushCommitSM(ES_Event_t CurrentEvent);
PushCommitSMState_t QueryPushCommit(void);

#endif