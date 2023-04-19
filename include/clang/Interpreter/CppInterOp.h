//--------------------------------------------------------------------*- C++ -*-
// CLING - the C++ LLVM-based InterpreterG :)
// author:  Vassil Vassilev <vvasilev@cern.ch>
//
// This file is dual-licensed: you can choose to license it under the University
// of Illinois Open Source License or the GNU Lesser General Public License. See
// LICENSE.TXT for details.
//------------------------------------------------------------------------------

#ifndef CPPINTEROP_CPPINTEROP_H
#define CPPINTEROP_CPPINTEROP_H

#include <string>
#include <vector>

namespace Cpp {
  using TCppIndex_t = size_t;
  using TCppScope_t = void*;
  using TCppType_t = void*;
  using TCppFunction_t = void*;
  using TCppFuncAddr_t = void*;
  using TCppSema_t = void *;
  using TInterp_t = void*;
  typedef void (*CallFuncWrapper_t)(void *, int, void **, void *);

  /// Enables or disables the debugging printouts on stderr.
  void EnableDebugOutput(bool value = true);

  ///\returns true if the debugging printouts on stderr are enabled.
  bool IsDebugOutputEnabled();

  bool IsNamespace(TCppScope_t scope);

  bool IsClass(TCppScope_t scope);
  // See TClingClassInfo::IsLoaded
  bool IsComplete(TCppScope_t scope);

  size_t SizeOf(TCppScope_t scope);
  bool IsBuiltin(TCppType_t type);

  bool IsTemplate(TCppScope_t handle);

  bool IsTemplateSpecialization(TCppScope_t handle);

  bool IsAbstract(TCppType_t klass);

  bool IsEnumScope(TCppScope_t handle);

  bool IsEnumType(TCppType_t type);

  /// We assume that smart pointer types define both operator* and
  /// operator->.
  bool IsSmartPtrType(TCppType_t type);

  TCppType_t GetEnumIntegerType(TCppScope_t handle);

  std::vector<TCppScope_t> GetEnumConstants(TCppScope_t scope);

  TCppIndex_t GetEnumConstantValue(TCppScope_t scope);

  size_t GetSizeOfType(TCppSema_t sema, TCppType_t type);

  bool IsVariable(TCppScope_t scope);

  std::string GetName(TCppType_t klass);

  std::string GetCompleteName(TCppSema_t sema, TCppType_t klass);

  std::string GetQualifiedName(TCppType_t klass);

  std::string GetQualifiedCompleteName(TCppSema_t sema, TCppType_t klass);

  std::vector<TCppScope_t> GetUsingNamespaces(TCppScope_t scope);

  TCppScope_t GetGlobalScope(TCppSema_t sema);

  TCppScope_t GetScope(TCppSema_t sema, const std::string &name,
                       TCppScope_t parent = 0);

  TCppScope_t GetScopeFromCompleteName(TCppSema_t sema,
                                       const std::string &name);

  TCppScope_t GetNamed(TCppSema_t sema, const std::string &name,
                       TCppScope_t parent = nullptr);

  TCppScope_t GetParentScope(TCppScope_t scope);

  TCppScope_t GetScopeFromType(TCppType_t type);

  TCppIndex_t GetNumBases(TCppType_t klass);

  TCppScope_t GetBaseClass(TCppType_t klass, TCppIndex_t ibase);

  bool IsSubclass(TInterp_t interp, TCppScope_t derived, TCppScope_t base);

  int64_t GetBaseClassOffset(TCppSema_t sema, TCppScope_t derived,
                             TCppScope_t base);

  std::vector<TCppFunction_t> GetClassMethods(TCppSema_t sema,
                                              TCppScope_t klass);

  bool HasDefaultConstructor(TCppScope_t scope);

  TCppScope_t GetDestructor(TCppScope_t scope);

  std::vector<TCppFunction_t> GetFunctionsUsingName(TCppSema_t sema,
                                                    TCppScope_t scope,
                                                    const std::string &name);

  TCppType_t GetFunctionReturnType(TCppFunction_t func);

  TCppIndex_t GetFunctionNumArgs(TCppFunction_t func);

  TCppIndex_t GetFunctionRequiredArgs(TCppFunction_t func);

  TCppType_t GetFunctionArgType(TCppFunction_t func, TCppIndex_t iarg);

  /// Returns a stringified version of a given function signature in the form:
  /// void N::f(int i, double d, long l = 0, char ch = 'a').
  std::string GetFunctionSignature(TCppFunction_t func);

  bool IsTemplatedFunction(TCppFunction_t func);

  bool ExistsFunctionTemplate(TCppSema_t sema, const std::string &name,
                              TCppScope_t parent = 0);

  bool IsPublicMethod(TCppFunction_t method);

  bool IsProtectedMethod(TCppFunction_t method);

  bool IsPrivateMethod(TCppFunction_t method);

  bool IsConstructor(TCppFunction_t method);

  bool IsDestructor(TCppFunction_t method);

  bool IsStaticMethod(TCppFunction_t method);

  TCppFuncAddr_t GetFunctionAddress(TInterp_t interp, TCppFunction_t method);

  bool IsVirtualMethod(TCppFunction_t method);

  std::vector<TCppScope_t> GetDatamembers(TCppScope_t scope);

  TCppScope_t LookupDatamember(TCppSema_t sema, const std::string &name,
                               TCppScope_t parent);

  TCppType_t GetVariableType(TCppScope_t var);

  intptr_t GetVariableOffset(TInterp_t interp, TCppScope_t var);

  bool IsPublicVariable(TCppScope_t var);

  bool IsProtectedVariable(TCppScope_t var);

  bool IsPrivateVariable(TCppScope_t var);

  bool IsStaticVariable(TCppScope_t var);

  bool IsConstVariable(TCppScope_t var);

  bool IsRecordType(TCppType_t type);

  bool IsPODType(TCppSema_t sema, TCppType_t type);

  TCppType_t GetUnderlyingType(TCppType_t type);

  std::string GetTypeAsString(TCppType_t type);

  TCppType_t GetCanonicalType(TCppType_t type);

  TCppType_t GetType(TCppSema_t sema, const std::string &type);

  TCppType_t GetComplexType(TCppSema_t sema, TCppType_t element_type);

  TCppType_t GetTypeFromScope(TCppScope_t klass);

  /// Check if a C++ type derives from another.
  bool IsTypeDerivedFrom(TInterp_t interp, TCppType_t derived, TCppType_t base);

  CallFuncWrapper_t GetFunctionCallWrapper(TInterp_t interp,
                                           TCppFunction_t func);

  /// Checks if a function declared is of const type or not
  bool IsConstMethod(TCppFunction_t method);

  /// Returns the default argument value as string.
  std::string GetFunctionArgDefault(TCppFunction_t func, TCppIndex_t param_index);

  /// Returns the argument name of function as string.
  std::string GetFunctionArgName(TCppFunction_t func, TCppIndex_t param_index);

  TInterp_t CreateInterpreter(const std::vector<const char *> &Args = {});

  TCppSema_t GetSema(TInterp_t interp);

  void AddSearchPath(TInterp_t interp, const char *dir, bool isUser = true,
                     bool prepend = false);

  /// Returns the resource-dir path.
  const char *GetResourceDir(TInterp_t interp);

  void AddIncludePath(TInterp_t interp, const char *dir);

  TCppIndex_t Declare(TInterp_t interp, const char *code, bool silent = false);

  /// Declares and runs a code snippet in \c code.
  ///\returns 0 on success
  int Process(TInterp_t interp, const char *code);

  const std::string LookupLibrary(TInterp_t interp, const char *lib_name);

  bool LoadLibrary(TInterp_t interp, const char *lib_path, bool lookup = true);

  std::string ObjToString(TInterp_t interp, const char *type, void *obj);

  struct TemplateArgInfo {
    TCppScope_t m_Type;
    const char* m_IntegralValue;
    TemplateArgInfo(TCppScope_t type, const char* integral_value = nullptr)
      : m_Type(type), m_IntegralValue(integral_value) {}
  };
  TCppScope_t InstantiateClassTemplate(TInterp_t interp, TCppScope_t tmpl,
                                       TemplateArgInfo *template_args,
                                       size_t template_args_size);

  std::vector<std::string> GetAllCppNames(TCppScope_t scope);

  void DumpScope(TCppScope_t scope);

  namespace DimensionValue {
    enum : long int {
      UNKNOWN_SIZE = -1,
    };
  }

  std::vector<long int> GetDimensions(TCppType_t type);
} // end namespace Cpp

#endif // CPPINTEROP_CPPINTEROP_H
