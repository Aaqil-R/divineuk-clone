// JavaScript Document
(function ($) {
$(document).ready(function(){
  $('.popups').each(function(){
	  $(this).attr('href',$(this).attr('href')+'?geo=none');
  });
});
}(jQuery));