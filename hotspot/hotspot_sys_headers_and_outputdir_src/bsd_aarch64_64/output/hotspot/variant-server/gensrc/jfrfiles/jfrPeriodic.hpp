/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef JFRFILES_JFRPERIODICEVENTSET_HPP
#define JFRFILES_JFRPERIODICEVENTSET_HPP

#include "utilities/macros.hpp"
#if INCLUDE_JFR
#include "jfrfiles/jfrEventIds.hpp"
#include "memory/allocation.hpp"

enum PeriodicType {BEGIN_CHUNK, INTERVAL, END_CHUNK};

class JfrPeriodicEventSet : public AllStatic {
 public:
  static void requestEvent(JfrEventId id, jlong timestamp, PeriodicType periodicType) {
    _timestamp = Ticks(timestamp);
    _type = periodicType;
    switch(id) {
  
      case JfrResidentSetSizeEvent:
        requestResidentSetSize();
        break;
  
      case JfrGCHeapMemoryUsageEvent:
        requestGCHeapMemoryUsage();
        break;
  
      case JfrGCHeapMemoryPoolUsageEvent:
        requestGCHeapMemoryPoolUsage();
        break;
  
      case JfrNativeMemoryUsageEvent:
        requestNativeMemoryUsage();
        break;
  
      case JfrNativeMemoryUsageTotalEvent:
        requestNativeMemoryUsageTotal();
        break;
  
      case JfrJVMInformationEvent:
        requestJVMInformation();
        break;
  
      case JfrOSInformationEvent:
        requestOSInformation();
        break;
  
      case JfrVirtualizationInformationEvent:
        requestVirtualizationInformation();
        break;
  
      case JfrInitialSystemPropertyEvent:
        requestInitialSystemProperty();
        break;
  
      case JfrInitialEnvironmentVariableEvent:
        requestInitialEnvironmentVariable();
        break;
  
      case JfrSystemProcessEvent:
        requestSystemProcess();
        break;
  
      case JfrCPUInformationEvent:
        requestCPUInformation();
        break;
  
      case JfrCPUTimeStampCounterEvent:
        requestCPUTimeStampCounter();
        break;
  
      case JfrCPULoadEvent:
        requestCPULoad();
        break;
  
      case JfrThreadCPULoadEvent:
        requestThreadCPULoad();
        break;
  
      case JfrThreadContextSwitchRateEvent:
        requestThreadContextSwitchRate();
        break;
  
      case JfrCompilerQueueUtilizationEvent:
        requestCompilerQueueUtilization();
        break;
  
      case JfrNetworkUtilizationEvent:
        requestNetworkUtilization();
        break;
  
      case JfrJavaThreadStatisticsEvent:
        requestJavaThreadStatistics();
        break;
  
      case JfrClassLoadingStatisticsEvent:
        requestClassLoadingStatistics();
        break;
  
      case JfrClassLoaderStatisticsEvent:
        requestClassLoaderStatistics();
        break;
  
      case JfrSymbolTableStatisticsEvent:
        requestSymbolTableStatistics();
        break;
  
      case JfrStringTableStatisticsEvent:
        requestStringTableStatistics();
        break;
  
      case JfrThreadAllocationStatisticsEvent:
        requestThreadAllocationStatistics();
        break;
  
      case JfrPhysicalMemoryEvent:
        requestPhysicalMemory();
        break;
  
      case JfrSwapSpaceEvent:
        requestSwapSpace();
        break;
  
      case JfrExecutionSampleEvent:
        requestExecutionSample();
        break;
  
      case JfrNativeMethodSampleEvent:
        requestNativeMethodSample();
        break;
  
      case JfrThreadDumpEvent:
        requestThreadDump();
        break;
  
      case JfrNativeLibraryEvent:
        requestNativeLibrary();
        break;
  
      case JfrModuleRequireEvent:
        requestModuleRequire();
        break;
  
      case JfrModuleExportEvent:
        requestModuleExport();
        break;
  
      case JfrCompilerStatisticsEvent:
        requestCompilerStatistics();
        break;
  
      case JfrCompilerConfigurationEvent:
        requestCompilerConfiguration();
        break;
  
      case JfrCodeCacheStatisticsEvent:
        requestCodeCacheStatistics();
        break;
  
      case JfrCodeCacheConfigurationEvent:
        requestCodeCacheConfiguration();
        break;
  
      case JfrIntFlagEvent:
        requestIntFlag();
        break;
  
      case JfrUnsignedIntFlagEvent:
        requestUnsignedIntFlag();
        break;
  
      case JfrLongFlagEvent:
        requestLongFlag();
        break;
  
      case JfrUnsignedLongFlagEvent:
        requestUnsignedLongFlag();
        break;
  
      case JfrDoubleFlagEvent:
        requestDoubleFlag();
        break;
  
      case JfrBooleanFlagEvent:
        requestBooleanFlag();
        break;
  
      case JfrStringFlagEvent:
        requestStringFlag();
        break;
  
      case JfrObjectCountEvent:
        requestObjectCount();
        break;
  
      case JfrG1HeapRegionInformationEvent:
        requestG1HeapRegionInformation();
        break;
  
      case JfrGCConfigurationEvent:
        requestGCConfiguration();
        break;
  
      case JfrGCSurvivorConfigurationEvent:
        requestGCSurvivorConfiguration();
        break;
  
      case JfrGCTLABConfigurationEvent:
        requestGCTLABConfiguration();
        break;
  
      case JfrGCHeapConfigurationEvent:
        requestGCHeapConfiguration();
        break;
  
      case JfrYoungGenerationConfigurationEvent:
        requestYoungGenerationConfiguration();
        break;
  
      case JfrShenandoahHeapRegionInformationEvent:
        requestShenandoahHeapRegionInformation();
        break;
  
      case JfrFinalizerStatisticsEvent:
        requestFinalizerStatistics();
        break;
  
      case JfrJavaAgentEvent:
        requestJavaAgent();
        break;
  
      case JfrNativeAgentEvent:
        requestNativeAgent();
        break;
  
      default:
        break;
      }
    }

 private:

  static void requestResidentSetSize(void);

  static void requestGCHeapMemoryUsage(void);

  static void requestGCHeapMemoryPoolUsage(void);

  static void requestNativeMemoryUsage(void);

  static void requestNativeMemoryUsageTotal(void);

  static void requestJVMInformation(void);

  static void requestOSInformation(void);

  static void requestVirtualizationInformation(void);

  static void requestInitialSystemProperty(void);

  static void requestInitialEnvironmentVariable(void);

  static void requestSystemProcess(void);

  static void requestCPUInformation(void);

  static void requestCPUTimeStampCounter(void);

  static void requestCPULoad(void);

  static void requestThreadCPULoad(void);

  static void requestThreadContextSwitchRate(void);

  static void requestCompilerQueueUtilization(void);

  static void requestNetworkUtilization(void);

  static void requestJavaThreadStatistics(void);

  static void requestClassLoadingStatistics(void);

  static void requestClassLoaderStatistics(void);

  static void requestSymbolTableStatistics(void);

  static void requestStringTableStatistics(void);

  static void requestThreadAllocationStatistics(void);

  static void requestPhysicalMemory(void);

  static void requestSwapSpace(void);

  static void requestExecutionSample(void);

  static void requestNativeMethodSample(void);

  static void requestThreadDump(void);

  static void requestNativeLibrary(void);

  static void requestModuleRequire(void);

  static void requestModuleExport(void);

  static void requestCompilerStatistics(void);

  static void requestCompilerConfiguration(void);

  static void requestCodeCacheStatistics(void);

  static void requestCodeCacheConfiguration(void);

  static void requestIntFlag(void);

  static void requestUnsignedIntFlag(void);

  static void requestLongFlag(void);

  static void requestUnsignedLongFlag(void);

  static void requestDoubleFlag(void);

  static void requestBooleanFlag(void);

  static void requestStringFlag(void);

  static void requestObjectCount(void);

  static void requestG1HeapRegionInformation(void);

  static void requestGCConfiguration(void);

  static void requestGCSurvivorConfiguration(void);

  static void requestGCTLABConfiguration(void);

  static void requestGCHeapConfiguration(void);

  static void requestYoungGenerationConfiguration(void);

  static void requestShenandoahHeapRegionInformation(void);

  static void requestFinalizerStatistics(void);

  static void requestJavaAgent(void);

  static void requestNativeAgent(void);

 static Ticks timestamp(void);
 static Ticks _timestamp;
 static PeriodicType type(void);
 static PeriodicType _type;
};

#endif // INCLUDE_JFR
#endif // JFRFILES_JFRPERIODICEVENTSET_HPP
