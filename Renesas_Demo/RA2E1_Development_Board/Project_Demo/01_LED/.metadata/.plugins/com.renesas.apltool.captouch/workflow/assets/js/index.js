/**
 *  ステップのクリック時に展開/折り畳みを行う
 */
$(".list-parent .list-header").click(function (e) {
	$(".list-sub .list-header").css("transition", "all 0.1s ease");
	$(this).parent().toggleClass("close");
});

/** 外部HTML読み込み（不使用） **/
$(".load").each(function (i, el) {
	$(el).load("./load_file/" + $(el).attr("id") + ".html");
});

/**
 *  ステップのサブ項目クリック時にクリック箇所をアクティブにする＆コンテンツエリア表示切替
 */
$(".list-group .list-sub .list-header").click(function (e) {
	activateStep($(this));
	set_fixbox();
});

/**
 *  ISDQEKBN-497 縦長モード時のコンテンツエリアクリック時に、クリック箇所をアクティブにする
 */
$(".list-content").click(function (e) {
	activateStep($(this));
});

function activateStep(element) {
	// ステップの折り畳みアニメーション無し
	$(".list-sub .list-header").css("transition", "none;");
	// クリックした箇所をアクティブにする
	$(".active").removeClass("active");
	$(".selected").removeClass("selected");
	element.parents('.list-parent').addClass("active");
	element.parent().addClass("selected");
	// クリックした箇所に対応するナビゲーション部分をアクティブにする
	$("#nav_" + (element.parents('.list-parent').attr("id").split("_")[1])).addClass("active");
}

$(".nav-item").click(function (e) {
	let id = $(this).attr("id").split("_")[1];

	$(".list-sub .list-header").css("transition", "none;");

	$(".active").removeClass("active");
	$(".selected").removeClass("selected");

	$("#list_" + id).addClass("active");
	$("#list_" + id + " .list-sub").first().addClass("selected");
	$("#nav_" + id).addClass("active");
	set_fixbox();

	// ISDQEKBN-488 ワークフローを縦長スタイルにした際に、ナビゲーションバーから対象のステップに画面がジャンプするように改善
	var elm = $(".list-sub.selected").parents(".list-parent").get(0);
	var navHight = $(".nav-item").get(0).offsetHeight;
	var pos = elm.getBoundingClientRect().top;
	scrollBy(0, pos - navHight);
});

let menucnt = $(".list-sub").length;

$(".btn_up").click(function (e) {
	let idx = $(".list-sub.selected").index(".list-sub");
	idx--;
	while (idx >= 0
		&& ($(".list-sub").eq(idx).hasClass("element-hidden")
			|| ($(".list-sub").eq(idx).parents(".list-parent").hasClass("element-hidden")))) {
		idx--;
	}
	if (idx >= 0) {
		$(".list-sub .list-header").css("transition", "none;");
		$(".selected").removeClass("selected");
		$(".active").removeClass("active");
		$(".list-sub").eq(idx).addClass("selected");
		$(".list-sub").eq(idx).parents('.list-parent').addClass("active");
		let id = $(".list-sub").eq(idx).parents('.list-parent').attr("id").split("_")[1];
		$("#nav_" + id).addClass("active");
		set_fixbox();
	}
});

$(".btn_down").click(function (e) {
	let idx = $(".list-sub.selected").index(".list-sub");
	idx++;
	while (idx < menucnt
		&& ($(".list-sub").eq(idx).hasClass("element-hidden")
			|| ($(".list-sub").eq(idx).parents(".list-parent").hasClass("element-hidden")))) {
		idx++;
	}
	if (idx < menucnt) {
		$(".list-sub .list-header").css("transition", "none;");
		$(".selected").removeClass("selected");
		$(".active").removeClass("active");
		$(".list-sub").eq(idx).addClass("selected");
		$(".list-sub").eq(idx).parents('.list-parent').addClass("active");
		let id = $(".list-sub").eq(idx).parents('.list-parent').attr("id").split("_")[1];
		$("#nav_" + id).addClass("active");
		set_fixbox();
	}

});

// プロジェクト選択 コンボボックス
$('#select-project').on('change', () => { window.location.href = 'qe-wfcmd-select-project-changed' });
// タッチI/F構成の選択 コンボボックス
$('#select-tif-config').on('change', () => { window.location.href = 'qe-wfcmd-select-tif-config-changed' });
// タッチI/F構成の編集 ボタン
$('#btn-modify-tif-config').on('click', () => { window.location.href = 'qe-wfcmd-btn-modify-tif-config-click' });
// 調整を開始する(エミュレータ接続) ボタン
$('#btn-start-tuning').on('click', (e) => {
	if (e.shiftKey) {
		window.location.href = 'qe-wfcmd-btn-start-tuning-click-with-shift';
	} else {
		window.location.href = 'qe-wfcmd-btn-start-tuning-click';
	}
});
// 調整を開始する(シリアル接続) ボタン
$('#btn-start-serial-tuning').on('click', (e) => {
	if (e.shiftKey) {
		window.location.href = 'qe-wfcmd-btn-start-serial-tuning-click-with-shift';
	} else {
		window.location.href = 'qe-wfcmd-btn-start-serial-tuning-click';
	}
});
// 高度な設定を有効にする チェックボックス
$('#checkbox-advanced-setting').on('click', () => { window.location.href = 'qe-wfcmd-checkbox-advanced-setting-click' });
$('#checkbox-advanced-serial-tuning-setting').on('click', () => { window.location.href = 'qe-wfcmd-checkbox-advanced-serial-tuning-setting-click' });
// 調整結果の確認 ボタン
$('#btn-display-tuning-result').on('click', () => { window.location.href = 'qe-wfcmd-btn-display-tuning-result-click' });
$('#btn-display-serial-tuning-result').on('click', () => { window.location.href = 'qe-wfcmd-btn-display-tuning-result-click' });
// 調整用ファイルを出力する ボタン
$('#btn-output-serial-tuning-files').on('click', (e) => {
	if (e.shiftKey) {
		window.location.href = 'qe-wfcmd-btn-output-serial-tuning-files-click-with-shift';
	} else {
		window.location.href = 'qe-wfcmd-btn-output-serial-tuning-files-click';
	}
});
// ファイルを出力する ボタン
$('#btn-output-tuning-files').on('click', (e) => {
	if (e.shiftKey) {
		window.location.href = 'qe-wfcmd-btn-output-tuning-files-click-with-shift';
	} else {
		window.location.href = 'qe-wfcmd-btn-output-tuning-files-click';
	}
});
// 外部トリガを使用する チェックボックス
$('#checkbox-external-trigger').on('click', () => { window.location.href = 'qe-wfcmd-checkbox-external-trigger-click' });
// 診断コードを使用する チェックボックス
$('#checkbox-diagnostic-code').on('click', () => { window.location.href = 'qe-wfcmd-checkbox-diagnostic-code-click' });
// API互換モードを使用する チェックボックス
$('#checkbox-api-compatibility-mode').on('click', () => { window.location.href = 'qe-wfcmd-checkbox-api-compatibility-mode-click' });
// ジェスチャ環境を導入する ボタン
$('#btn-gesture-environment').on('click', () => { window.location.href = 'qe-wfcmd-btn-gesture-environment-click' });
// ジェスチャ構成の選択 コンボボックス
$('#select-gesture-config').on('change', () => { window.location.href = 'qe-wfcmd-select-gesture-config-changed' });
// ジェスチャの構成を編集する ボタン
$('#btn-modify-gesture-config').on('click', () => { window.location.href = 'qe-wfcmd-btn-modify-gesture-config-click' });
// ジェスチャを登録する ボタン
$('#btn-recording-gesture').on('click', () => { window.location.href = 'qe-wfcmd-btn-recording-gesture-click' });
// ジェスチャのAI学習を開始する ボタン
$('#btn-training-gesture').on('click', () => { window.location.href = 'qe-wfcmd-btn-training-gesture-click' });
// ジェスチャのCソースを生成する ボタン
$('#btn-output-gesture-files').on('click', () => { window.location.href = 'qe-wfcmd-btn-output-gesture-files-click' });
// タッチレスボタン環境を導入する ボタン
$('#btn-touchless-environment').on('click', () => { window.location.href = 'qe-wfcmd-btn-touchless-environment-click' });
// タッチレスボタンデータを登録する ボタン
$('#btn-recording-touchless').on('click', () => { window.location.href = 'qe-wfcmd-btn-recording-touchless-click' });
// タッチレスボタンのAI学習を開始する ボタン
$('#btn-training-touchless').on('click', () => { window.location.href = 'qe-wfcmd-btn-training-touchless-click' });
// タッチレスボタンのCソースを生成する ボタン
$('#btn-output-touchless-files').on('click', () => { window.location.href = 'qe-wfcmd-btn-output-touchless-files-click' });
// 例を表示する ボタン
$('#btn-sample-code').on('click', () => { window.location.href = 'qe-wfcmd-btn-sample-code-click' });
// ボーレート テキストボックスのKeypressイベントハンドラ
function baudRateKeypressHandler(e, href) {
	if (e.key === "Enter") {
		window.location.href = href;
	} else if (e.keyCode < 48 || 57 < e.keyCode) {
		// 数字以外は入力不可
		return false;
	}
	return true;
}
// ボーレート テキストボックスのPasteイベントハンドラ
function baudRatePasteHandler(e) {
	// 数字以外の文字列の貼り付けを禁止
	const pattern = /^\d*$/;
	var pasted;
	if (e.originalEvent.clipboardData && e.originalEvent.clipboardData.getData) {
		pasted = e.originalEvent.clipboardData.getData('text/plain');
	}
	if (pattern.test(pasted) === false) {
		e.preventDefault();
	}
}
// ボーレート テキストボックス(モニタリングの開始(シリアル))
$('#text-baudrate').on('focusout', () => { window.location.href = 'qe-wfcmd-text-baudrate-focusout' })
$('#text-baudrate').on('keypress', (e) => {
	return baudRateKeypressHandler(e, 'qe-wfcmd-text-baudrate-keypress-enter');
});
$('#text-baudrate').on('paste', (e) => baudRatePasteHandler(e));
// ボーレート テキストボックス(調整の開始(シリアル))
$('#text-baudrate-serial-tuning').on('focusout', () => { window.location.href = 'qe-wfcmd-text-baudrate-focusout-serial-tuning' })
$('#text-baudrate-serial-tuning').on('keypress', (e) => {
	return baudRateKeypressHandler(e, 'qe-wfcmd-text-baudrate-keypress-enter-serial-tuning');
});
$('#text-baudrate-serial-tuning').on('paste', (e) => baudRatePasteHandler(e));
// ポート番号 コンボボックス(モニタリングの開始(シリアル))
$('#select-port').on('focusin', () => { window.location.href = 'qe-wfcmd-select-port-focusin' });
$('#select-port').on('change', () => { window.location.href = 'qe-wfcmd-select-port-change' });
// ポート番号 コンボボックス(調整の開始(シリアル))
$('#select-port-serial-tuning').on('focusin', () => { window.location.href = 'qe-wfcmd-select-port-focusin-serial-tuning' });
$('#select-port-serial-tuning').on('change', () => { window.location.href = 'qe-wfcmd-select-port-change-serial-tuning' });
// 接続する ボタン
$('#btn-connect-serial').on('click', () => { window.location.href = 'qe-wfcmd-btn-connect-serial-click' });
// ビューを開く(エミュレータ接続) ボタン
$('#btn-open-monitor-view-emulator').on('click', () => { window.location.href = 'qe-wfcmd-btn-open-monitor-view-click' });
// ビューを開く(シリアル接続) ボタン
$('#btn-open-monitor-view-serial').on('click', () => { window.location.href = 'qe-wfcmd-btn-open-monitor-view-click' });

function set_fixbox() {
	let id = $(".active").attr("id").split("_")[1];
	$(".selected").find(".list-content").append($(".fixed-box"));
	$(".active").removeClass("close");

	// added by pis tajima
	if (htmlInitialized) {
		window.location.href = 'qe-wfcmd-set-fixbox';
	}
}

$(window).resize(function () {
	set_fixbox();
});


// Initialize Swiper
var swiper = new Swiper(".mySwiper", {
	slidesPerView: 1,
	spaceBetween: 30,
	slidesPerGroup: 1,
	loop: true,
	loopFillGroupWithBlank: true,
	pagination: {
		el: ".swiper-pagination",
		clickable: true,
	},
	navigation: {
		nextEl: ".swiper-button-next",
		prevEl: ".swiper-button-prev",
	},
});

// added by pis tajima
var htmlInitialized = false;

set_fixbox();

// added by pis tajima
$(function () {
	htmlInitialized = true;
});