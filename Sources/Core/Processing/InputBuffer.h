/**
 * @file Core/Processing/InputBuffer.h
 * Contains the header of class Core::Processing::InputBuffer.
 *
 * @copyright Copyright (C) 2020 Sarmad Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <https://alusus.org/alusus_license_1_0>.
 */
//==============================================================================

#ifndef CORE_PROCESSING_INPUTBUFFER_H
#define CORE_PROCESSING_INPUTBUFFER_H

namespace Core { namespace Processing
{

/**
 * @brief A buffer for input characters with character positions.
 * @ingroup core_processing
 *
 * This class contains a buffer for input characters and manages the positions
 * of the characters within the source code. The class doesn't store the
 * position of each character, instead it follows a more memory efficient
 * method by storing only the jumps in positions. In other words, it only
 * stores the position when the character's position can't be computed
 * from the positions of previous characters.
 */
class InputBuffer
{
  //============================================================================
  // Data Types

  /**
   * @brief Properties of a part in the input buffer.
   *
   * Defines the length and starting position of a group of characters in the
   * buffer.
   */
  private: struct CharacterGroup
  {
    /// The location of the first character in the group.
    Data::SourceLocationRecord sourceLocation;

    /// The number of characters in the group.
    Int length;
  };


  //============================================================================
  // Member Variables

  /**
   * @brief The buffer of input characters.
   *
   * This string contains the list of characters in the buffer.
   */
  private: WStr charBuffer;

  /**
   * @brief Manages the positions of characters in the source code.
   *
   * This array is used to store the positions of the characters in the source
   * code. It tries to minimize the required memory by storing only the
   * position of the first character in each group of consecutive characters.
   * The positions of the other characters in the group can then be easily
   * computed. This array is needed to handle cases where there is a jump in
   * the positions of characters in the source code. Such jumps can occure if
   * parts of the source code isn't feeded to the lexer (excluded by a
   * preprocessor for example).
   */
  private: std::vector<CharacterGroup> charGroups;


  //============================================================================
  // Constructor / Destructor

  public: InputBuffer()
  {
  }

  public: ~InputBuffer()
  {
  }


  //============================================================================
  // Member Functions

  /// @name Operations
  /// @{

  /// Push a new character to the end of the buffer.
  public: Bool push(WChar ch, Data::SourceLocationRecord const &sl, Bool force=false);

  /// Remove a group of characters from the beginning of the buffer.
  public: void remove(Int count);

  /// Remove all characters from the buffer
  public: void clear()
  {
    this->remove(this->getCharCount());
  }

  /// @}

  /// @name Data Retrieval Functions.
  /// @{

  /// Get a pointer to the characters stored in the buffer.
  public: WChar const* getChars()
  {
    return this->charBuffer.c_str();
  }

  /// Get the number of characters currently in the buffer.
  public: Int getCharCount()
  {
    return this->charBuffer.size();
  }

  /// Get the source location of the first character in the buffer.
  public: Data::SourceLocationRecord const& getSourceLocation() const
  {
    static Data::SourceLocationRecord nullSL;
    if (this->charGroups.size() == 0) return nullSL;
    else return this->charGroups.at(0).sourceLocation;
  }

  /// Get whether the buffer is full or not.
  public: Bool isFull();

  /// @}

}; // class

} } // namespace

#endif
