
#ifdef SABASAENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif // !SABASAENGINE_EXPORTS
