/**
 * @file Core/Data/Container.h
 * Contains the header of interface Data::Container.
 *
 * @copyright Copyright (C) 2015 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef DATA_CONTAINER_H
#define DATA_CONTAINER_H

namespace Core { namespace Data
{

// TODO: DOC

class Container : public IdentifiableInterface
{
  //============================================================================
  // Type Info

  INTERFACE_INFO(Container, IdentifiableInterface, "Core.Data", "Core", "alusus.net");


  //============================================================================
  // Signals

  // TODO: Use these signals in all implementations.

  /**
     * @brief A signal for enquiring whether the given content is in use.
     *
     * This signal is fired before removing any content from the list. This
     * is to make sure no one is still using this content. Anything handling
     * this signal should return true if it's using provided content object.
     */
  public: SIGNAL_WITH_ACK(contentInUseInquirer, (IdentifiableObject *content), (content));

  public: SIGNAL(indexChangeNotifier, (Int from, Int to), (from, to));

  public: SIGNAL(contentChangeNotifier, (Container *obj, ContentChangeOp op, Int index), (obj, op, index));


  //============================================================================
  // Abstract Functions

  public: virtual void set(Int index, IdentifiableObject *val) = 0;

  public: virtual void remove(Int index) = 0;

  public: virtual Word getCount() const = 0;

  public: virtual IdentifiableObject* get(Int index) const = 0;

}; // class

} } // namespace

#endif
