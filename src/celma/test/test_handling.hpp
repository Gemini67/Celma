
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::test::TestHandling.


#ifndef CELMA_TEST_TEST_HANDLING_HPP
#define CELMA_TEST_TEST_HANDLING_HPP


namespace celma { namespace test {


/// Helper class for test programs that allows to verify if an object was
/// default-created, copied or moved.<br>
/// Use this object either directly or as base class of your applications class.
/// Afterwards the flags can be checked to determine, which kind of constructor
/// was used to initialise a new object.<br>
/// A special handling is used for the destructor, since a normal member
/// variable would of course not work.
///
/// @since  1.11.0, 07.09.2018
class TestHandling
{
public:
   /// Default constructor.
   ///
   /// @param[in]  dtor_called_flag
   ///    Pointer to the flag to set when the destructor was called,
   ///    NULL (the default) if no flag needs to be set.
   /// @since  1.11.0, 07.09.2018
   explicit TestHandling( bool* dtor_called_flag = nullptr);

   /// Copy constructor. Sets the flag #mCopyCtor.<br>
   /// An eventually set #mpDtorCalled pointer is not copied.
   ///
   /// @param[in]  other  Ignored.
   /// @since  1.11.0, 07.09.2018
   explicit TestHandling( const TestHandling& other);

   /// Move constructor. Sets the flag #mMoveCtor.<br>
   /// An eventually set #mpDtorCalled pointer is not copied/moved.
   ///
   /// @param[in]  other  Ignored.
   /// @since  1.11.0, 07.09.2018
   TestHandling( TestHandling&& other);

   /// Destructor. Sets the flag that was passed to the constructor, if any.
   ///
   /// @since  1.11.0, 11.09.2018
   virtual ~TestHandling();

   /// For objects that were copy- or move-constructed: Allows to set the
   /// pointer to the flag that should be set when the destructor is called.
   ///
   /// @param[in]  dtor_called_flag
   ///    Pointer to the flag to set when the destructor is called.
   /// @since
   ///    1.11.0, 11.09.2018
   void setDtorFlag( bool& dtor_called_flag);

   /// Returns if the default constructor was called/used to create the current
   /// object.
   ///
   /// @return  \c true if the default constructor was called.
   /// @since  1.11.0, 07.09.2018
   bool defaultCtorCalled() const;

   /// Returns if the copy constructor was called/used to create the current
   /// object.
   ///
   /// @return  \c true if the copy constructor was called.
   /// @since  1.11.0, 07.09.2018
   bool copyCtorCalled() const;

   /// Returns if the move constructor was called/used to create the current
   /// object.
   ///
   /// @return  \c true if the move constructor was called.
   /// @since  1.11.0, 07.09.2018
   bool moveCtorCalled() const;

   /// Resets all the internal flags.
   ///
   /// @since  1.11.0, 07.09.2018
   void reset();

private:
   /// Set when the default constructor is called.
   bool   mDefaultCtor = false;
   /// Set when the copy constructor is called.
   bool   mCopyCtor = false;
   /// Set when the move constructor is called.
   bool   mMoveCtor = false;
   /// Pointer to the flag to set when the destructor is called.
   bool*  mpDtorCalled = nullptr;

}; // TestHandling


// inlined methods
// ===============


inline TestHandling::TestHandling( bool* dtor_called_flag):
   mpDtorCalled( dtor_called_flag)
{
   mDefaultCtor = true;
} // TestHandling::TestHandling


inline TestHandling::TestHandling( const TestHandling&)
{
   mCopyCtor = true;
} // TestHandling::TestHandling


inline TestHandling::TestHandling( TestHandling&&)
{
   mMoveCtor = true;
} // TestHandling::TestHandling


inline TestHandling::~TestHandling()
{
   if (mpDtorCalled != nullptr)
      *mpDtorCalled = true;
} // TestHandling::~TestHandling


inline void TestHandling::setDtorFlag( bool& dtor_called_flag)
{
   mpDtorCalled = &dtor_called_flag;
} // TestHandling::setDtorFlag

inline bool TestHandling::defaultCtorCalled() const
{
   return mDefaultCtor;
} // TestHandling::defaultCtorCalled


inline bool TestHandling::copyCtorCalled() const
{
   return mCopyCtor;
} // TestHandling::copyCtorCalled


inline bool TestHandling::moveCtorCalled() const
{
   return mMoveCtor;
} // TestHandling::moveCtorCalled


inline void TestHandling::reset()
{
   mDefaultCtor = false;
   mCopyCtor = false;
   mMoveCtor = false;
} // TestHandling::reset


} // namespace test
} // namespace celma


#endif   // CELMA_TEST_TEST_HANDLING_HPP


// =====  END OF test_handling.hpp  =====

