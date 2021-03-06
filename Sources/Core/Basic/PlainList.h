/**
 * @file Core/Basic/PlainList.h
 * Contains the header of class Core::Basic::PlainList.
 *
 * @copyright Copyright (C) 2020 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <https://alusus.org/alusus_license_1_0>.
 */
//==============================================================================

#ifndef CORE_BASIC_PLAINLIST_H
#define CORE_BASIC_PLAINLIST_H

namespace Core::Basic
{

template<class CTYPE> class PlainList : public PlainListBase<CTYPE, TiObject>
{
  //============================================================================
  // Type Info

  typedef PlainListBase<CTYPE, TiObject> _MyBase;
  TEMPLATE_TYPE_INFO(PlainList, _MyBase, "Core.Basic", "Core", "alusus.org", (CTYPE));


  //============================================================================
  // Constructors

  public: PlainList()
  {
  }

  public: PlainList(std::initializer_list<CTYPE*> const &args)
  {
    this->add(args);
  }

  public: virtual ~PlainList()
  {
    this->destruct();
  }

  public: static SharedPtr<PlainList> create(std::initializer_list<CTYPE*> const &args)
  {
    return std::make_shared<PlainList>(args);
  }


  //============================================================================
  // Member Functions

  /// @name Abstract Implementations
  /// @{

  protected: virtual CTYPE* prepareForSet(Int index, CTYPE *obj, Bool inherited, Bool newEntry)
  {
    return obj;
  }

  protected: virtual void finalizeSet(Int index, CTYPE *obj, Bool inherited, Bool newEntry)
  {
  }

  protected: virtual void prepareForUnset(Int index, CTYPE *obj, Bool inherited)
  {
  }

  /// @}

  /// @name Inheritted Functions
  /// @{

  public: void setBase(PlainList<CTYPE> *b)
  {
    PlainListBase<CTYPE, TiObject>::setBase(b);
  }

  public: PlainList<CTYPE>* getBase() const
  {
    return static_cast<PlainList<CTYPE>*>(this->base);
  }

  /// @}

}; // class

} // namespace

#endif
