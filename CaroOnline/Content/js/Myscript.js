var lastScrollTop = 0;
$(window).scroll(function (event) {
    var st = $(this).scrollTop();
    if (st > lastScrollTop ) {
        // downscroll code
        var t = $('#SideBar').innerHeight();
       // $("#SideBar").css('height',)
        $('#nav-fix-top').removeClass('fixed-top');
        $('#nav-fix-top').removeClass(' animated fadeInDown');
    } else if (lastScrollTop!=0) {
     
        $('#nav-fix-top').addClass('fixed-top');
        $('#nav-fix-top').addClass('animated fadeInDown');
        if (st < 100) {
            $('#nav-fix-top').removeClass('fixed-top');
            $('#nav-fix-top').removeClass('animated fadeInDown');
           
        }
        // upscroll code
    }
    lastScrollTop = st;
});



//$(window).scroll(function () {
//    if ($(this).scrollTop() > 400) {
//        $('#nav-fix-top').addClass('fixed-top');
//        //$('#UtiPost').show();

//        //$('.fx').fadeIn();
//        //$('.aria-contact').fadeIn();
//    } else {
//        $('#nav-fix-top').removeClass('fixed-top');
//       // $('#UtiPost').hide();
//    }
//    //if ($("#fotterStop").isVisible()) {
//    //    $("#UtiPost").hide();
//    //} else {
//    //    $("#UtiPost").show();
//    //}
//    //if ($('body').height() <= ($(window).height() + $(window).scrollTop()+200)) {
//    //    $('#UtiPost').hide();
//    //}

//});

$('.navbar .dropdown').hover(function () {
    $(this).find('.dropdown-menu').first().stop(true, true).slideDown(100);
}, function () {
    $(this).find('.dropdown-menu').first().stop(true, true).slideUp(95)
    });
$('.reviewRate').click(function () {
    $('.reviewRate').addClass('fa-star-o');
    $('.reviewRate').removeClass('yellow-text fa-star');

    var pos = parseInt($(this).data("pos"));
    if (pos < 3) {
        if (pos == 1) {
            $('#titleRate').text("Dở tệ");
        }
        if (pos == 2) {
            $('#titleRate').text("Tạm được");
        }
        $('#titleRate').removeClass('text-success');
        $('#titleRate').addClass('text-danger');
        //$('#iconRate').removeClass('fa-smile-o text-success');
        //$('#iconRate').addClass('fa-frown-o text-danger');
    } else {
        if (pos == 3) {
            $('#titleRate').text("Hay");
        }
        if (pos == 4) {
            $('#titleRate').text("Rất hay");
        }
        if (pos == 5) {
            $('#titleRate').text("Tuyệt vời");
        }
        $('#titleRate').removeClass('text-danger');
        $('#titleRate').addClass('text-success');
        //$('#iconRate').removeClass('fa-frown-o text-danger');
        //$('#iconRate').addClass('fa-smile-o text-success');
    }
    for (var i = 1; i <= pos; i++) {
        $('#star' + i).removeClass('fa-star-o');
        $('#star' + i).addClass("yellow-text fa-star")
    }
    //if ($(this).hasClass("yellow-text fa-star")) {
        
    //    $(this).addClass('fa-star-o');
    //    $(this).removeClass('yellow-text fa-star');
    //} else {
    //    $(this).removeClass('fa-star-o');
    //    $(this).addClass('yellow-text fa-star');
    //}
    
});

function moveScroller() {
    var $anchor = $("#scroller-anchor");
    var $scroller = $('#scroller');

    var move = function () {
        var st = $(window).scrollTop();
        var ot = $anchor.offset().top;
        if (st > ot) {
            $scroller.css({
                position: "fixed",
                top: "0px"
            });
        } else {
            $scroller.css({
                position: "relative",
                top: ""
            });
        }
    };
    $(window).scroll(move);
    move();
}

function stripUnicode(slug) {
    slug = slug.toLowerCase();
    slug = slug.replace(/á|à|ả|ạ|ã|ă|ắ|ằ|ẳ|ẵ|ặ|â|ấ|ầ|ẩ|ẫ|ậ/gi, 'a');
    slug = slug.replace(/é|è|ẻ|ẽ|ẹ|ê|ế|ề|ể|ễ|ệ/gi, 'e');
    slug = slug.replace(/i|í|ì|ỉ|ĩ|ị/gi, 'i');
    slug = slug.replace(/ó|ò|ỏ|õ|ọ|ô|ố|ồ|ổ|ỗ|ộ|ơ|ớ|ờ|ở|ỡ|ợ/gi, 'o');
    slug = slug.replace(/ú|ù|ủ|ũ|ụ|ư|ứ|ừ|ử|ữ|ự/gi, 'u');
    slug = slug.replace(/ý|ỳ|ỷ|ỹ|ỵ/gi, 'y');
    slug = slug.replace(/đ/gi, 'd');
    slug = slug.replace(/\`|\~|\!|\@|\#|\||\$|\%|\^|\&|\*|\(|\)|\+|\=|\,|\.|\/|\?|\>|\<|\'|\"|\:|\;|_/gi, '');
    slug = slug.replace(/ /gi, "-");
    slug = slug.replace(/\-\-\-\-\-/gi, '-');
    slug = slug.replace(/\-\-\-\-/gi, '-');
    slug = slug.replace(/\-\-\-/gi, '-');
    slug = slug.replace(/\-\-/gi, '-');
    slug = '@' + slug + '@';
    slug = slug.replace(/\@\-|\-\@|\@/gi, '');
    return slug;
}

function ChangeToSlug(title) {
   

    //Đổi chữ hoa thành chữ thường
    var slug = title.toLowerCase();

    //Đổi ký tự có dấu thành không dấu
    slug = slug.replace(/á|à|ả|ạ|ã|ă|ắ|ằ|ẳ|ẵ|ặ|â|ấ|ầ|ẩ|ẫ|ậ/gi, 'a');
    slug = slug.replace(/é|è|ẻ|ẽ|ẹ|ê|ế|ề|ể|ễ|ệ/gi, 'e');
    slug = slug.replace(/i|í|ì|ỉ|ĩ|ị/gi, 'i');
    slug = slug.replace(/ó|ò|ỏ|õ|ọ|ô|ố|ồ|ổ|ỗ|ộ|ơ|ớ|ờ|ở|ỡ|ợ/gi, 'o');
    slug = slug.replace(/ú|ù|ủ|ũ|ụ|ư|ứ|ừ|ử|ữ|ự/gi, 'u');
    slug = slug.replace(/ý|ỳ|ỷ|ỹ|ỵ/gi, 'y');
    slug = slug.replace(/đ/gi, 'd');
    //Xóa các ký tự đặt biệt
    slug = slug.replace(/\`|\~|\!|\@|\#|\||\$|\%|\^|\&|\*|\(|\)|\+|\=|\,|\.|\/|\?|\>|\<|\'|\"|\:|\;|_/gi, '');
    //Đổi khoảng trắng thành ký tự gạch ngang
    slug = slug.replace(/ /gi, "-");
    //Đổi nhiều ký tự gạch ngang liên tiếp thành 1 ký tự gạch ngang
    //Phòng trường hợp người nhập vào quá nhiều ký tự trắng
    slug = slug.replace(/\-\-\-\-\-/gi, '-');
    slug = slug.replace(/\-\-\-\-/gi, '-');
    slug = slug.replace(/\-\-\-/gi, '-');
    slug = slug.replace(/\-\-/gi, '-');
    //Xóa các ký tự gạch ngang ở đầu và cuối
    slug = '@' + slug + '@';
    slug = slug.replace(/\@\-|\-\@|\@/gi, '');
    //In slug ra textbox có id “slug”
    return slug;
}
function FormatString(c) {
    var str = c;
   
    // str= str.toLowerCase();  
    str = str.replace(/à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ/g, "a");
    str = str.replace(/è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ/g, "e");
    str = str.replace(/ì|í|ị|ỉ|ĩ/g, "i");
    str = str.replace(/ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ/g, "o");
    str = str.replace(/ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ/g, "u");
    str = str.replace(/ỳ|ý|ỵ|ỷ|ỹ/g, "y");
    str = str.replace(/đ/g, "d");
    str = str.replace(/!|@|%|\^|\*|\(|\)|\+|\=|\<|\>|\?|,|\:|\;|\'||\"|\&|\#|\[|\]|~|$|_/g, "");
    // tìm và thay thế các kí tự đặc biệt trong chuỗi sang kí tự - 
    str = str.replace(/-+-/g, ""); //thay thế 2- thành 1- 
    str = str.replace(/^\-+|\-+$/g, "");

    while (str.indexOf("  ") > 0) {
        str = str.replace(/  /g, " ");
    }

    return str;
    //   return str;  
}

function bodauTiengViet(str) {

    str = str.toLowerCase();
    str = str.replace(/à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ/g, 'a');
    str = str.replace(/è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ/g, 'e');
    str = str.replace(/ì|í|ị|ỉ|ĩ/g, 'i');
    str = str.replace(/ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ/g, 'o');
    str = str.replace(/ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ/g, 'u');
    str = str.replace(/ỳ|ý|ỵ|ỷ|ỹ/g, 'y');
    str = str.replace(/đ/g, 'd');
    str = str.replace(/\W+/g, ' ');
    str = str.replace(/\s/g, '-');
    return str;
}