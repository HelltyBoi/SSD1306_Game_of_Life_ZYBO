proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000

start_step init_design
set rc [catch {
  create_msg_db init_design.pb
  create_project -in_memory -part xc7z010clg400-1
  set_property board_part digilentinc.com:zybo:part0:2.0 [current_project]
  set_property design_mode GateLvl [current_fileset]
  set_property webtalk.parent_dir C:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.cache/wt [current_project]
  set_property parent.project_path C:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.xpr [current_project]
  set_property ip_repo_paths c:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.cache/ip [current_project]
  set_property ip_output_repo c:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.cache/ip [current_project]
  add_files -quiet C:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.runs/synth_1/SSD1306_example_TopWrapper.dcp
  read_xdc -ref SSD1306_example_bd_processing_system7_0_0 -cells inst c:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.srcs/sources_1/bd/SSD1306_example_bd/ip/SSD1306_example_bd_processing_system7_0_0/SSD1306_example_bd_processing_system7_0_0.xdc
  set_property processing_order EARLY [get_files c:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.srcs/sources_1/bd/SSD1306_example_bd/ip/SSD1306_example_bd_processing_system7_0_0/SSD1306_example_bd_processing_system7_0_0.xdc]
  read_xdc C:/Users/0036472890/workspace/SSD1306_example/SSD1306_example.srcs/constrs_1/imports/workspace/Zybo-Master.xdc
  link_design -top SSD1306_example_TopWrapper -part xc7z010clg400-1
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
}

start_step opt_design
set rc [catch {
  create_msg_db opt_design.pb
  catch {write_debug_probes -quiet -force debug_nets}
  opt_design 
  write_checkpoint -force SSD1306_example_TopWrapper_opt.dcp
  report_drc -file SSD1306_example_TopWrapper_drc_opted.rpt
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
}

start_step place_design
set rc [catch {
  create_msg_db place_design.pb
  catch {write_hwdef -file SSD1306_example_TopWrapper.hwdef}
  place_design 
  write_checkpoint -force SSD1306_example_TopWrapper_placed.dcp
  report_io -file SSD1306_example_TopWrapper_io_placed.rpt
  report_utilization -file SSD1306_example_TopWrapper_utilization_placed.rpt -pb SSD1306_example_TopWrapper_utilization_placed.pb
  report_control_sets -verbose -file SSD1306_example_TopWrapper_control_sets_placed.rpt
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
}

start_step route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force SSD1306_example_TopWrapper_routed.dcp
  report_drc -file SSD1306_example_TopWrapper_drc_routed.rpt -pb SSD1306_example_TopWrapper_drc_routed.pb
  report_timing_summary -warn_on_violation -max_paths 10 -file SSD1306_example_TopWrapper_timing_summary_routed.rpt -rpx SSD1306_example_TopWrapper_timing_summary_routed.rpx
  report_power -file SSD1306_example_TopWrapper_power_routed.rpt -pb SSD1306_example_TopWrapper_power_summary_routed.pb
  report_route_status -file SSD1306_example_TopWrapper_route_status.rpt -pb SSD1306_example_TopWrapper_route_status.pb
  report_clock_utilization -file SSD1306_example_TopWrapper_clock_utilization_routed.rpt
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
}

start_step write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  catch { write_mem_info -force SSD1306_example_TopWrapper.mmi }
  write_bitstream -force SSD1306_example_TopWrapper.bit 
  catch { write_sysdef -hwdef SSD1306_example_TopWrapper.hwdef -bitfile SSD1306_example_TopWrapper.bit -meminfo SSD1306_example_TopWrapper.mmi -file SSD1306_example_TopWrapper.sysdef }
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
}

