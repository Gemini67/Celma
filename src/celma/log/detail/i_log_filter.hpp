
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::detail::ILogFilter.


#ifndef CELMA_LOG_DETAIL_I_LOG_FILTER_HPP
#define CELMA_LOG_DETAIL_I_LOG_FILTER_HPP


namespace celma { namespace log { namespace detail {


class LogMsg;


/// Interface definition of log filters.
/// @since  0.3, 19.06.2016
class ILogFilter
{
public:
   /// List of filter types:
   enum FilterTypes
   {
      ftMaxLevel,      //!< Filter by maximum log level.
      ftMinLevel,      //!< Filter by minimum log level.
      ftLevel,         //!< Filter for a log level.
      ftClasses,       //!< Filter by log classes.
      ftProcessName,   //!< Filter by process name.
      ftUserDefined,   //!< User defined filter.
      ftInvalid        //!< Initialisation value.
   };

   /// Returns if a filter type filters on log levels.
   /// @param[in]  ft  The filter type to check.
   /// @return  \c true if the specified filter type filters on log levels.
   /// @since  0.3, 19.06.2016
   static bool isLevelFilter( FilterTypes ft);

   /// Constructor, stores the filter type.
   /// @param[in]  ft  The type of the filter.
   /// @since  0.3, 19.06.2016
   ILogFilter( FilterTypes ft);

   /// Empty, virtual destructor.
   /// @since  0.3, 19.06.2016
   virtual ~ILogFilter() { };

   /// Returns the type of this filter.
   /// @return  The type of this filter.
   /// @since  0.3, 19.06.2016
   FilterTypes filterType() const;

   /// Template method: This method is called to check if a message is accepted
   /// by the filter and can be passed on.<br>
   /// Internally calls, pass().
   /// @param[in]  msg  The message to check.
   /// @return  \c true if the message is accepted.
   /// @since  0.3, 19.06.2016
   bool passFilter( const LogMsg& msg) const;

protected:
   /// The type of the filter.
   const FilterTypes  mFilterType;

private:
   /// Interface.<br>
   /// Implementations should check the message.
   /// @param[in]  msg  The message to check.
   /// @return  \c true if the message is accepted by the filter.
   /// @since  0.3, 19.06.2016
   virtual bool pass( const LogMsg& msg) const = 0;

}; // ILogFilter


// inlined methods
// ===============


inline bool ILogFilter::isLevelFilter( FilterTypes ft)
{
  return (ft == ftMaxLevel) || (ft == ftMinLevel) || (ft == ftLevel);
} // end ILogFilter::isLevelFilter


inline ILogFilter::ILogFilter( FilterTypes ft):
   mFilterType( ft)
{
} // end ILogFilter::ILogFilter


inline ILogFilter::FilterTypes ILogFilter::filterType() const
{
   return mFilterType;
} // end ILogFilter::filterType


inline bool ILogFilter::passFilter( const LogMsg& msg) const
{
   return pass( msg);
} // end ILogFilter::passFilter


} // namespace detail
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_DETAIL_I_LOG_FILTER_HPP


// =========================  END OF i_log_filter.hpp  =========================

