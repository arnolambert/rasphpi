PHP_ARG_ENABLE(rasphpi,
  [Whether to enable the "rasphpi" extension],
  [ --enabel-rasphpi    Enable "rasphpi" extension support])

if test PHP_RASPHPI != "no"; then
  PHP_SUBST(RASPHPI_SHARED_LIBADD)
  PHP_NEW_EXTENSION(rasphpi, rasphpi.c, $ext_shared)
fi
