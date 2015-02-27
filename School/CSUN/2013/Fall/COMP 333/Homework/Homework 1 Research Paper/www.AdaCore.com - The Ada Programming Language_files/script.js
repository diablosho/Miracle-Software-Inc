$(function() {
    $('ul.page_tabs').tabs('div.panes > div.pane', {history: true});
    $('#accordion').tabs('#accordion div.pane', {
        tabs: 'strong', effect: 'slide', initialIndex: null
    });
    $('.video_overlay[rel]').overlay({
        mask: 'black'
    });

    /* GNAT Tracker Drop Down */
    var gnattracker_toggled = false;
    $('.gnattracker a.toggle').click(function() {
        if (gnattracker_toggled) {
            $(this).parents('.gnattracker').removeClass('toggled');
            gnattracker_toggled = false;
        } else {
            $(this).parents('.gnattracker').addClass('toggled');
            gnattracker_toggled = true;
        }
        return false;
    });
    $(document).bind('click', function(e) {
        var $clicked = $(e.target);
        if (! $clicked.parents().hasClass('gnattracker')) {
            $('.gnattracker').removeClass('toggled');
            gnattracker_toggled = false;
        }
    });


    /* Auto truncate */
    $('.truncated').jTruncate({
        length: 200,
        minTrail: 20,
        moreText: '(show more)',
        lessText: '(show less)'
    });

    /* manual truncation */
    $('.truncated_toggle a').click(function() {
        // See more and See less
        if ($(this).parent().prev('.truncated_hidden').is(':hidden')) {
            $(this).parent().prev('.truncated_hidden').show();
            $(this).html('See Less');
        } else {
            $(this).parent().prev('.truncated_hidden').hide();
            $(this).html('See More');
        }
        // See More that disappears
        if ($(this).parent().next('.truncated_hidden').is(':hidden')) {
            $(this).parent().next('.truncated_hidden').show();
            $(this).parent().hide();
        }
        return false;
    });


    $('ul.page_tabs').tabs('div.panes .pane');

    if (!Modernizr.input.placeholder) {
        $('.placeholderfallback').show();
        $('.placeholderfallback').css('display', 'block');
    }
    
    // New Video reveal Functionality in use on Lectures/playlists.
    $(".video_reveal").click(function(){
		
		$('#video_player_pane div').load($(this).attr('href') + ' iframe', function() {
			$("#video_player_pane").slideDown(500);
		});
		
		return false;
	});
});
