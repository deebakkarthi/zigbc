/* pid$target::realloc:entry,pid$target::malloc:entry { @a[probemod, probefunc] = count(); } */
/**/
/* pid$target:libsystem_c::entry { */
/* @a[probemod,probefunc] = count(); */
/* } */
/*pid$target:libsystem_malloc:malloc:entry,*/
pid$target:libsystem_malloc:malloc_type_malloc:entry,
pid$target:libsystem_malloc:realloc:entry
{
@[probemod,execname] = count();
ustack();
}
