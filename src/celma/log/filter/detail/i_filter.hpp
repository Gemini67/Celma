
/*==
**
**    ####   ######  #       #    #   ####
**   #    #  #       #       ##  ##  #    #
**   #       ###     #       # ## #  ######    (C) 2016-2018 Rene Eng
**   #    #  #       #       #    #  #    #        LGPL
**    ####   ######  ######  #    #  #    #
**
**
--*/


/// @file
/// See documentation of class celma::log::filter::detail::IFilter.


#ifndef CELMA_LOG_FILTER_DETAIL_I_FILTER_HPP
#define CELMA_LOG_FILTER_DETAIL_I_FILTER_HPP


namespace celma { namespace log {


namespace detail {
class LogMsg;
}


namespace filter { namespace detail {


/// Interface definition of log filters.
/// @since  1.15.1, 09.01.2018  (moved and renamed)
/// @since  0.3, 19.06.2016
class IFilter
{
public:
   /// List of filter types:
   enum class FilterTypes
   {
      maxLevel,      //!< Filter by maximum log level.
      minLevel,      //!< Filter by minimum log level.
      level,         //!< Filter for a log level.
      classes,       //!< Filter by log classes.
      processName,   //!< Filter by process name.
      userDefined,   //!< User defined filter.
      invalid        //!< Initialisation value.
   };

   /// Returns if a filter type filters on log levels.
   /// @param[in]  ft  The filter type to check.
   /// @return  \c true if the specified filter type filters on log levels.
   /// @since  0.3, 19.06.2016
   static bool isLevelFilter( FilterTypes ft);

   /// Constructor, stores the filter type.
   /// @param[in]  ft  The type of the filter.
   /// @since  0.3, 19.06.2016
   IFilter( FilterTypes ft);

   /// Empty, virtual destructor.
   /// @since  0.3, 19.06.2016
   virtual ~IFilter() { };

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
   bool passFilter( const log::detail::LogMsg& msg) const;

protected:
   /// The type of the filter.
   const FilterTypes  mFilterType;

private:
   /// Interface.<br>
   /// Implementations should check the message.
   /// @param[in]  msg  The message to check.
   /// @return  \c true if the message is accepted by the filter.
   /// @since  0.3, 19.06.2016
   virtual bool pass( const log::detail::LogMsg& msg) const = 0;

}; // IFilter


// inlined methods
// ===============


inline bool IFilter::isLevelFilter( FilterTypes ft)
{
  return (ft == FilterTypes::maxLevel) || (ft == FilterTypes::minLevel) ||
         (ft == FilterTypes::level);
} // IFilter::isLevelFilter


inline IFilter::IFilter( FilterTypes ft):
   mFilterType( ft)
{
} // IFilter::IFilter


inline IFilter::FilterTypes IFilter::filterType() const
{
   return mFilterType;
} // IFilter::filterType


inline bool IFilter::passFilter( const log::detail::LogMsg& msg) const
{
   return pass( msg);
} // IFilter::passFilter


} // namespace detail
} // namespace filter
} // namespace log
} // namespace celma


#endif   // CELMA_LOG_FILTER_DETAIL_I_FILTER_HPP


// =====  END OF i_log_filter.hpp  =====

