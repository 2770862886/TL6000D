#ifndef _STRINGS_H__
#define _STRINGS_H__

#include "build_config.h"

#if LANG_SET == 0 /* Simplified Chinese version */

#define STR_LOGO            "REGAR"
#define STR_CONNECTED       "������"
#define STR_NOT_CONNECTED   "δ����"
#define STR_WELCOME         "��ӭ�μ�"
#define STR_CONFERENCE_INFO "������Ϣ"

#define STR_SIGNED          "�ѱ���"
#define STR_NOT_SIGNED      "δ����"
#define STR_SIGN_FAIL       "����ʧ��"

#define STR_VOTED           "�ѱ��"

#define STR_SIGN_PRESS      "��������"
#define STR_SIGN_CARD       "��忨"
#define STR_SIGN_END        "��������"
#define STR_CARD_NONE       "δ�忨"
#define STR_CARD_ERR        "���Ŵ���"
#define STR_CARD_VALID      "��Ч��"
#define STR_CARD_INVALID    "��Ч��"

#define STR_VOTE5_START     "��ѡ��"
#define STR_VOTE5_END       "ѡ�ٽ���"

#define STR_VOTE_START      "����"
#define STR_VOTE_REMAIN     "����ѡ%02d��"
#define STR_VOTE_END        "�������"

#define STR_CANDIDATE_1     "��ѡ�ˢ�"
#define STR_CANDIDATE_2     "��ѡ�ˢ�"
#define STR_CANDIDATE_3     "��ѡ�ˢ�"
#define STR_CANDIDATE_4     "��ѡ�ˢ�"
#define STR_CANDIDATE_5     "��ѡ�ˢ�"

#define STR_DISCUSS_ONGOING "������"
#define STR_DISCUSS_APPLY   "������"
#define STR_DISCUSS_OPEN    "��Ͳ��"
#define STR_DISCUSS_CLOSE   "��Ͳ�ر�"

#define STR_REMARK_START    "�������"
#define STR_REMARK_END      "�������"

#define STR_INPUT_NUMBER    "�����ּ�"
#define STR_INPUT           "�밴��"

#define STR_VALID_ON_FIRST  "��һ������Ч"
#define STR_VALID_ON_LAST   "��󰴼���Ч"

#define STR_CHANGE_ADDR     "�޸ĳ�"

#define STR_VOTE_YES        "�޳�"
#define STR_VOTE_NO         "����"
#define STR_VOTE_ABSTAIN    "��Ȩ"

#define STR_REMARK_SATISFIED        "����"
#define STR_REMARK_ADEQUATE         "��������"
#define STR_REMARK_DISAPPOINTED     "������"

#define STR_PLUG_EARPHONE   "������"

#elif LANG_SET == 1 /* English version */

#define STR_LOGO            "REGAR"
#define STR_CONNECTED       "CONNECTED"
#define STR_NOT_CONNECTED   "DISCONNECTED"
#define STR_WELCOME         "WELCOME"
#define STR_CONFERENCE_INFO "CONF INFO"

#define STR_SIGNED          "REG'D"
#define STR_NOT_SIGNED      "NOT REG'D"
#define STR_SIGN_FAIL       "REG.FAILED"

#define STR_VOTED           "VOTE CASTED"

#define STR_SIGN_PRESS      "PUSH TO REG"
#define STR_SIGN_CARD       "INSERT CARD"
#define STR_SIGN_END        "REG.END"
#define STR_CARD_NONE       "NO CARD"
#define STR_CARD_ERR        "CARD ERROR"
#define STR_CARD_VALID      "VALID CARD"
#define STR_CARD_INVALID    "INVALID CARD"

#define STR_VOTE5_START     "CAST A VOTE"
#define STR_VOTE5_END       "ELECTION END"

#define STR_VOTE_START      "CAST A VOTE"
#define STR_VOTE_REMAIN     "CHOOSE MORE %02d"
#define STR_VOTE_END        "VOTING END"

#define STR_CANDIDATE_1     "CANDID. #001"
#define STR_CANDIDATE_2     "CANDID. #002"
#define STR_CANDIDATE_3     "CANDID. #003"
#define STR_CANDIDATE_4     "CANDID. #004"
#define STR_CANDIDATE_5     "CANDID. #005"

#define STR_DISCUSS_ONGOING "ONLINE"
#define STR_DISCUSS_APPLY   "REG.TO TALK"
#define STR_DISCUSS_OPEN    "MIC ON"
#define STR_DISCUSS_CLOSE   "MIC OFF"

#define STR_REMARK_START    "CAST A REMARK"
#define STR_REMARK_END      "REMARK END"

#define STR_INPUT_NUMBER    "PRESS A NUM"
#define STR_INPUT           "PUSH BUTTON"

#define STR_VALID_ON_FIRST  "1ST VALID"
#define STR_VALID_ON_LAST   "LAST VALID"

#define STR_CHANGE_ADDR     "CHANGE TO"

#define STR_VOTE_YES        "YES"
#define STR_VOTE_NO         "NO"
#define STR_VOTE_ABSTAIN    "ABSTAIN"

#define STR_REMARK_SATISFIED        "SATISFIED"
#define STR_REMARK_ADEQUATE         "ADEQUATE"
#define STR_REMARK_DISAPPOINTED     "DISAPPOINTED"

#define STR_PLUG_EARPHONE   "PLUG EARPHONE"

#endif

#endif /* STRINGS_H_ */
