#ifndef __Q_FUSE_H
#define __Q_FUSE_H

#include "QDefines.h"
#include "QNode.h"

// tolua_begin
namespace quick {
// tolua_end


class QFuse { // tolua_export
public:
    // BOUND, PRIVATE
    // tolua_begin
    QFuse();
    ~QFuse();

    bool isAvailable();
    void init(const char* apiKey);
    void show(const char* zone);
    bool checkLoaded(const char* zone);
    void load(const char* zone);
    void registerPushNotification(const char* projectId);

    enum EParameterKey
    {
        CURRENCY_CURRENCY, 
        CURRENCY_BALANCE,
        LEVEL_LEVEL,
        GENDER_GENDER,
        AGE_AGE,
        BIRTHDAY_DAY,
        BIRTHDAY_MONTH,
        BIRTHDAY_YEAR,
        PUSHTOKEN
    };

    // tolua_end

    Q_READONLY_VARIABLE( EParameterKey, parameterKey);

    

}; // tolua_export

// tolua_begin
}
// tolua_end

#endif // __Q_FUSE_H