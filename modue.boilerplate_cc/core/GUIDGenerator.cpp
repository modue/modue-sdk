#include "GUIDGenerator.h"
#include <uuid/uuid.h>

std::string GenerateGUID()
{
  uuid_t uuid;
  uuid_generate(uuid);
  char uuidStr[37];
  uuid_unparse(uuid, uuidStr);
  return std::string(uuidStr);
}
