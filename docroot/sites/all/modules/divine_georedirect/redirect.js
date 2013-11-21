// JavaScript Document
(function ($) {
$(document).ready(function(){
	console.info(Drupal.settings);
	//redirect if cookie is set
	if($.cookie("redirect") == "yes"){
	//redirect
	window.location = Drupal.settings.divine_georedirect.url;
	}
	//they have the cookie set but don't want redirected
	else if($.cookie("redirect") == 'no') {
	}
	//the cookie hasn't been set yet so ask them if they want to set it
	else {
		$('body').append('<div id="redirect_box"><h1>Welcome to ' + Drupal.settings.divine_georedirect.site_name + '</h1><p>This is our ' + Drupal.settings.divine_georedirect.server_origin + ' site.</p><div><a href="#" id="redirect_no">Stay here.</a></div><div><a href="#" id="redirect_yes">Go to the site of your country.</a></div><div><input type="checkbox" id="redirect_remember" checked="checked" /><label>Remember my selection</label></div></div>');
	}
	$('#redirect_yes').click(function(){
		if ($('#redirect_remember:checked').val() == 'on'){
			$.cookie("redirect","yes",{path:'/'});
		alert("To access this site in the future, you must clear your cookies!");
		}
		window.location = Drupal.settings.divine_georedirect.url;
	});
	$('#redirect_no').click(function(){
		if($('#redirect_remember:checked').val() == 'on'){
				$.cookie("redirect","no",{path:'/'});
		}
		$('#redirect_box').css('display','none');
	});
});
}(jQuery));