#ifndef _STRINGS_H__
#define _STRINGS_H__

#include "build_config.h"

#if LANG_SET == 0 /* Simplified Chinese version */

#define STR_LOGO            "REGAR"
#define STR_CONNECTED       "已连接"
#define STR_NOT_CONNECTED   "未连接"
#define STR_WELCOME         "欢迎参加"
#define STR_CONFERENCE_INFO "会议信息"

#define STR_SIGNED          "已报到"
#define STR_NOT_SIGNED      "未报到"
#define STR_SIGN_FAIL       "申请失败"

#define STR_VOTED           "已表决"

#define STR_SIGN_PRESS      "按报到键"
#define STR_SIGN_CARD       "请插卡"
#define STR_SIGN_END        "报到结束"
#define STR_CARD_NONE       "未插卡"
#define STR_CARD_ERR        "卡号错误"
#define STR_CARD_VALID      "有效卡"
#define STR_CARD_INVALID    "无效卡"

#define STR_VOTE5_START     "请选举"
#define STR_VOTE5_END       "选举结束"

#define STR_VOTE_START      "请表决"
#define STR_VOTE_REMAIN     "还可选%02d人"
#define STR_VOTE_END        "表决结束"

#define STR_CANDIDATE_1     "候选人①"
#define STR_CANDIDATE_2     "候选人②"
#define STR_CANDIDATE_3     "候选人③"
#define STR_CANDIDATE_4     "候选人④"
#define STR_CANDIDATE_5     "候选人⑤"

#define STR_DISCUSS_ONGOING "讨论中"
#define STR_DISCUSS_APPLY   "申请中"
#define STR_DISCUSS_OPEN    "话筒打开"
#define STR_DISCUSS_CLOSE   "话筒关闭"

#define STR_REMARK_START    "按评议键"
#define STR_REMARK_END      "评议结束"

#define STR_INPUT_NUMBER    "按数字键"
#define STR_INPUT           "请按键"

#define STR_VALID_ON_FIRST  "第一按键有效"
#define STR_VALID_ON_LAST   "最后按键有效"

#define STR_CHANGE_ADDR     "修改成"

#define STR_VOTE_YES        "赞成"
#define STR_VOTE_NO         "反对"
#define STR_VOTE_ABSTAIN    "弃权"

#define STR_REMARK_SATISFIED        "满意"
#define STR_REMARK_ADEQUATE         "基本满意"
#define STR_REMARK_DISAPPOINTED     "不满意"

#define STR_PLUG_EARPHONE   "请插耳机"

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
